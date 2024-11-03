//catatan pin yang digunakan pada hardware seuai desain pcb :
// SENSOR ULTRASONIC : - PIN TRIGGER = 4
//                     - PIN ECHO = 2
// SENSOR FLOW       : - PIN DT = 18 ((DISINI KARENA GAADA SENSOR FLOW MAKA MENGGUNAKAN PENGGANTI SIMULASI ROTARY ENCODER)) 
//                     - PIN CLK = 19 
// FLOW CONTROL      : - SOLENOID_V = 13
//                   : - POMPA AIR  = 14
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AiEsp32RotaryEncoder.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define MAX_ENTRIES 5             // Keep track of the last 5 entries
#define VOLUME_PER_ROTATION 0.6  // 0.6 cm^3 per 18-degree rotation
#define ENCODER_DT 18             // Rotary Encoder DT Pin
#define ENCODER_CLK 19            // Rotary Encoder CLK Pin
#define NO_FLOW_THRESHOLD 500     // No-Flow time threshold (ms)

// WiFi and MQTT setup
const char* ssid = "Lmao";           // Replace with your WiFi SSID
const char* password = "**********";    // Replace with your WiFi Password
const char* mqtt_server = "broker.mqtt.cool"; // Broker address
const int mqtt_port = 1883;

// MQTT topics
const char* topic_flowRate = "sensor/flowRate";
const char* topic_percentage = "sensor/percentage";
const char* topic_solenoid_control = "control/solenoid"; // Control topic for solenoid

// WiFi and MQTT Client setup
WiFiClient espClient;
PubSubClient client(espClient);

// LCD Setup
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

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
int solenoidState = 0; // the state of the solenoid
int tresMin = 25, tresMax = 90; // Pump activation tank min and max values(in percent)
                      // (activates at min, stops at max)

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
  distance = duration * 0.034 / 2;

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
  if (digitalRead(solenoidOpenBtn) == HIGH) {
    solenoidState = 1;
  }
  else if (digitalRead(solenoidCloseBtn) == HIGH) {
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
      Serial.print(client.state());
      delay(2000);  // Wait and retry connection
    }
  }
}

// Your existing setup code
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Initialize MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // LCD and sensor setup (same as your code)
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Kucing");

  // Rest of your sensor setup
  ultrasonicSetup();
  pinMode(solenoidPin, OUTPUT);
  pinMode(pompaAirPin, OUTPUT);
  pinMode(solenoidOpenBtn, INPUT);
  pinMode(solenoidCloseBtn, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), readEncoder, FALLING);
  timeNow = millis();
}

void loop() {
  // Reconnect to MQTT if not connected
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

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
  String flowRateStr = String(flowRate);
  String percentageStr = String(percentage);

  // Publish flowRate and percentage to MQTT topics
  client.publish(topic_flowRate, flowRateStr.c_str());
  client.publish(topic_percentage, percentageStr.c_str());

  // Delay before the next measurement
  delay(100);
}
