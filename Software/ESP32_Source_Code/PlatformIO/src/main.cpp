/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete instructions at https://RandomNerdTutorials.com/esp32-wi-fi-manager-asyncwebserver/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/
//catatan pin yang digunakan pada hardware seuai desain pcb :
// SENSOR ULTRASONIC : - PIN TRIGGER = 12
//                     - PIN ECHO = 14
// SENSOR FLOW       : - PIN DATA = D5  ((DISINI KARENA GAADA SENSOR FLOW MAKA MENGGUNAKAN PENGGANTI SIMULASI ROTARY ENKODER)) 
//                     - PIN DT = GPI018, CLK = GPIO19

#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AiEsp32RotaryEncoder.h>
#include <PubSubClient.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "LittleFS.h"

// Define Encoder Flow Sensor Constants
#define MAX_ENTRIES 5             // Keep track of the last 5 entries
#define VOLUME_PER_ROTATION 0.6   // 0.6 cm^3 per 18-degree rotation
#define ENCODER_DT 18             // Rotary Encoder DT Pin
#define ENCODER_CLK 19            // Rotary Encoder CLK Pin
#define NO_FLOW_THRESHOLD 500     // No-Flow time threshold (ms)

// MQTT Setup
const char* mqtt_server = "broker.mqtt.cool"; // Broker address
const int mqtt_port = 1883;

// MQTT topics
const char* topic_sensor = "AQUASMART/sensor";
const char* topic_flowRate = "sensor/flowRate";
const char* topic_percentage = "sensor/percentage";
const char* topic_solenoid = "sensor/solenoid";
const char* topic_pump = "sensor/pump";
const char* topic_solenoid_control = "control/solenoid"; // Control topic for solenoid

// WiFi and MQTT Client setup
WiFiClient espClient;
PubSubClient client(espClient);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_4 = "gateway";

//Variables to save values from HTML form
String ssid;
String pass;
String ip;
String gateway;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";

IPAddress localIP;
//IPAddress localIP(192, 168, 1, 200); // hardcoded

// Set your Gateway IP address
IPAddress localGateway;
//IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 0, 0);

// Timer variables
unsigned long previousMillis = 0;
const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds)

// Pin assignments for Ultrasonic sensor
const int trigPin = 4;  // Ultrasonic Trigger Pin
const int echoPin = 2;  // Ultrasonic Echo Pin

// Flow Control Components pins
const int solenoidPin = 13;
const int pompaAirPin = 14;
const int solenoidOpenBtn = 34;
const int solenoidCloseBtn = 35;

// List to hold the last 5 delay times (in ms)
float delay_times[MAX_ENTRIES];
int count = 0;  // To track the number of entries added

// variables
long duration;      // Variable for Ultrasonic sensor duration
int distance;       // Variable for distance measured by the Ultrasonic sensor
int percentage;     // Variable for water level percentage
long timeNow;       // current time
long timeLast;      // previous recorded time (for flow rate calc)
int lastClk = HIGH; // previous encoder clk pin state
int newClk;         // current encoder clk pin state
int encoderDelay = 0;   // delay get from encoder
float flowRate;     // calculated flow-rate
int solenoidState = 1; // the state of the solenoid
int tresMin = 25, tresMax = 90; // Pump activation tank min and max values(in percent) // (activates at min, stops at max)
int setupMode = 0;
uint64_t timeAtReading = esp_timer_get_time();
uint64_t timeToPublish = 1000;

// Set LCD I2C address
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

// Function to convert distance to percentage (2 cm = 0%, 400 cm = 100%)
int convertToPercentage(int distance, int jarakMin, int jarakMax) {
  if (distance >= 400) return 0;
  if (distance <= 2) return 100;
  return map(distance, jarakMax, jarakMin, 0, 100);  // Mapping the value between 0 and 100%
}

float calculateFlowRate(float delay_time_ms) {
    // If delay exceeds threshold, return 0 (flow stopped)
    if (delay_time_ms > NO_FLOW_THRESHOLD) {
        return 0.0;  // Flow stopped
    }
    // Otherwise, calculate flow rate
    float delay_time_sec = delay_time_ms / 1000.0;  // Convert to seconds
    float flow_rate = VOLUME_PER_ROTATION / delay_time_sec;  // cm³/s
    return flow_rate;
}

// Function to calculate the moving average of flow rates
float calculateMovingAverage(float new_delay_time) {
    // If less than 5 values, add to the list directly
    if (count < MAX_ENTRIES) {
        delay_times[count] = new_delay_time;
        count++;
    } else {
        // Shift values to the left (remove the oldest value)
        for (int i = 0; i < MAX_ENTRIES - 1; i++) {
            delay_times[i] = delay_times[i + 1];
        }
        // Add the new delay time to the end
        delay_times[MAX_ENTRIES - 1] = new_delay_time;
    }

    // Calculate instantaneous flow rates for the last 5 delay times
    float total_flow_rate = 0;
    for (int i = 0; i < count; i++) {
        total_flow_rate += calculateFlowRate(delay_times[i]);
    }

    // Calculate the moving average flow rate
    float moving_average = total_flow_rate / count;
    return moving_average;
}

void ultrasonicSetup(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void ultrasonicTrigger(){
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void ultrasonicCalculate(){
  // Measure echo duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance from duration (in cm)
  distance = duration * 0.0343 / 2;

  // Convert distance to percentage (2 cm = 0%, 400 cm = 100%)
  percentage = convertToPercentage(distance, 2, 400);
}

void ultrasonicDisplayDistance(){
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  lcd.print(distance);
}

void ultrasonicDisplayPercentage(){
  Serial.print("Percentage: ");
  Serial.print(percentage);
  Serial.println(" %");
  lcd.setCursor(0, 0);
  lcd.print("WtrLvl: ");
  lcd.print(percentage);
  lcd.print("%");
}

void readEncoder() {
  timeNow = millis();
  encoderDelay = 1 + timeNow - timeLast;
  timeLast = timeNow;
}

void encoderDisplayFlowRate(){
  Serial.print("Flow Rate: ");
  Serial.print(flowRate);
  Serial.println(" cm^3/s");
  lcd.setCursor(0, 1);
  lcd.print("flRate: ");
  lcd.print(flowRate);
  lcd.print(" cm3");
}

void flowconCheck(){
  if(percentage < tresMin){
    digitalWrite(pompaAirPin, HIGH);
  }
  else if(percentage >= tresMax){
    digitalWrite(pompaAirPin, LOW);
  }
}

void solenoidCheck(){
  if (digitalRead(solenoidOpenBtn) == LOW) {
    solenoidState = 1;
  }
  else if (digitalRead(solenoidCloseBtn) == LOW) {
    solenoidState = 0;
  }
}

void solenoidCState(){
  digitalWrite(solenoidPin, solenoidState);
}

// Callback function to handle incoming MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  // Convert the payload to a string
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Check if the message is for solenoid control
  if (String(topic) == topic_solenoid_control) {
    if (message == "1") {
      solenoidState = 1; // Turn ON solenoid
    } else if (message == "0") {
      solenoidState = 0; // Turn OFF solenoid
    }
    // Update solenoid pin state
    digitalWrite(solenoidPin, solenoidState);
    Serial.print("Solenoid State updated to: ");
    Serial.println(solenoidState);
  }
}

// MQTT reconnect function
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe(topic_solenoid_control);
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(2000);  // Wait and retry connection
    }
  }
}

// Initialize LittleFS
void initLittleFS() {
  if (!LittleFS.begin(true)) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  Serial.println("LittleFS mounted successfully");
}

// Read File from LittleFS
String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return String();
  }
  
  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;     
  }
  return fileContent;
}

// Write file to LittleFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
}

// Initialize WiFi
bool initWiFi() {
  if(ssid=="" || ip==""){
    Serial.println("Undefined SSID or IP address.");
    return false;
  }

  if(digitalRead(solenoidOpenBtn) == LOW || digitalRead(solenoidCloseBtn) == LOW){
    Serial.println("Wifi Setup Mode");
    return false;
  }

  WiFi.mode(WIFI_STA);
  localIP.fromString(ip.c_str());
  localGateway.fromString(gateway.c_str());

  
  //if (!WiFi.config(localIP, localGateway, subnet)){
  //  Serial.println("STA Failed to configure");
  //  return false;
  //}
  
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;

  while(WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failed to connect.");
      return false;
    }
  }

  Serial.println(WiFi.localIP());
  return true;
}


void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  initLittleFS();

  // lcd setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Kucing");

  // Set up ultrasonic sensor pins
  ultrasonicSetup();
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), readEncoder, FALLING);
  timeNow = millis();

  // Rest of sensor setup
  ultrasonicSetup();
  pinMode(solenoidPin, OUTPUT);
  pinMode(pompaAirPin, OUTPUT);
  pinMode(solenoidOpenBtn, INPUT);
  pinMode(solenoidCloseBtn, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), readEncoder, FALLING);
  timeNow = millis();
  
  // Load values saved in LittleFS
  ssid = readFile(LittleFS, ssidPath);
  pass = readFile(LittleFS, passPath);
  ip = readFile(LittleFS, ipPath);
  gateway = readFile (LittleFS, gatewayPath);
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(ip);
  Serial.println(gateway);

  if(initWiFi()) {
    Serial.println("Connected to WiFi");
    // Initialize MQTT
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
  }
  else {
    setupMode = 1;
    // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP); 

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/wifimanager.html", "text/html");
    });
    
    server.serveStatic("/", LittleFS, "/");
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        const AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid value
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            // Write file to save value
            writeFile(LittleFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(LittleFS, passPath, pass.c_str());
          }
          // HTTP POST ip value
          if (p->name() == PARAM_INPUT_3) {
            ip = p->value().c_str();
            Serial.print("IP Address set to: ");
            Serial.println(ip);
            // Write file to save value
            writeFile(LittleFS, ipPath, ip.c_str());
          }
          // HTTP POST gateway value
          if (p->name() == PARAM_INPUT_4) {
            gateway = p->value().c_str();
            Serial.print("Gateway set to: ");
            Serial.println(gateway);
            // Write file to save value
            writeFile(LittleFS, gatewayPath, gateway.c_str());
          }
          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: " + ip);
      delay(3000);
      ESP.restart();
    });
    server.begin();
  }
}

void loop() {
  if (!client.connected() && setupMode == 0) {
    reconnect();
  }
  client.loop();
  if ((millis() - timeAtReading) >= timeToPublish && setupMode == 0){
    timeAtReading = millis();
    if (millis() - timeNow >= NO_FLOW_THRESHOLD) {
      encoderDelay = 1000;
    }
    // Calculate the moving average flow rate
    flowRate = calculateMovingAverage(encoderDelay);

    // Trigger ultrasonic and calculate distance, percentage
    ultrasonicTrigger();
    ultrasonicCalculate();
    flowconCheck();
    solenoidCheck();
    solenoidCState();

    // Display data on the Serial Monitor and LCD
    lcd.clear();
    ultrasonicDisplayPercentage();
    encoderDisplayFlowRate();

    // Convert `flowRate` and `percentage` to strings for publishing
    String solenoidStr = String(solenoidState);
    String pumpStr = String(digitalRead(pompaAirPin));
    String flowRateStr = String(flowRate);
    String percentageStr = String(percentage);
    String allData = flowRateStr + String(",") + percentageStr + String(",") + solenoidStr + String(",") + pumpStr;

    // Publish flowRate and percentage to MQTT topics
    //client.publish(topic_pump, pumpStr.c_str());
    //client.publish(topic_solenoid, solenoidStr.c_str());
    //client.publish(topic_flowRate, flowRateStr.c_str());
    //client.publish(topic_percentage, percentageStr.c_str());
    client.publish(topic_sensor, allData.c_str());
  }
  //else{
  //  Serial.println("Test");
  //}
}


