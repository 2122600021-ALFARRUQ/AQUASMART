![flyer](https://github.com/user-attachments/assets/078f21d2-d860-4f91-8444-4bdbab0fef4a)

# AQUA SMART
<div align="center">
    <img src="https://github.com/user-attachments/assets/5526e358-7520-43ce-8ac9-127eed4594b0" alt="AQUA SMART Logo" width="200">
</div>

## **Supported By:**  
🌟 **Dosen Pengampu:** Akhmad Hendriawan, S.T., M.T.  *(NIP: 197501272002121003)*  
🎓 **Mata Kuliah:** IOT dan Jaringan Sensor  
🎯 **Program Studi:** Sarjana Terapan Teknik Elektronika  
🏫 **Politeknik Elektronika Negeri Surabaya**  


# Daftar Isi

- [Deskripsi](#deskripsi)
- [Komponen](#komponen)
   * [1. ESP32](#1-esp32)
   * [2. Sensor Ultrasonic](#2-sensor-ultrasonic)
   * [3. Flow Sensor](#3-flow-sensor)
   * [4. Adaptor 12V 2A](#4-adaptor-12v-2a)
   * [5. Solenoid Valve](#5-solenoid-valve)
   * [6. Modul Relay](#6-modul-relay)
- [Diagram Arsitektur](#diagram-arsitektur)
- [Tim Pengembang](#tim-pengembang)
- [Timeline Pengembangan](#timeline-pengembangan)
- [Rincian Pengeluaran Biaya](#rincian-pengeluaran-biaya)
- [Hardware](#hardware)
  * [1. Schematic Rangkaian](#1-schematic-rangkaian)
  * [2. Desain PCB](#2-desain-pcb)
  * [3. 3D Model PCB](#3-3d-model-pcb)
- [Software](#software)
  * [1. Flowchart](#1-flowchart)
  * [2. Simulasi Wokwi](#2-simulasi-wokwi)
  * [3. Node-Red](#3-node-red)
  * [4. Sequence Diagram](#4-sequence-diagram)
  * [5. Class Diagram](#5-class-diagram)
- [Dokumentasi](#dokumentasi)
  * [1. Video Percobaan Pengiriman Data dari ESP32 ke Broker MQTT](#1-video-percobaan-pengiriman-data-dari-esp32-ke-broker-mqtt)
  * [2. Video Simulasi Wokwi](#2-video-simulasi-wokwi)
  * [3. Video Simulasi Aplikasi](#3-video-simulasi-aplikasi)
    * [3.1 Video Simulasi Aplikasi Web](#31-video-simulasi-aplikasi-web)
    * [3.2 Video Simulasi Aplikasi Mobile](#32-video-simulasi-aplikasi-mobile)
  * [4. Video Pengujian Sensor Ultrasonik](#4-video-pengujian-sensor-ultrasonik)
  * [5. Video Pengujian Hardware](#5-video-pengujian-hardware)
  * [6. Video Penggunaan Alat](#5-video-penggunaan-alat)
  * [7. Proses Pengerjaan](#6-proses-pengerjaan)
  * [8. Video Pengiklanan](#7-video-pengiklanan)
  * [9. Video Presentasi](#8-video-presentasi)

# Deskripsi
Sistem Monitoring Penggunaan Air Berbasis IoT ini dirancang untuk membantu rumah tangga dalam memantau penggunaan dan ketersediaan air secara real-time. Menggunakan ESP32 sebagai kontroler utama, sistem ini memanfaatkan sensor aliran air (Flow Sensor) untuk melacak jumlah air yang digunakan serta sensor ultrasonik untuk mengukur level air di dalam tangki penyimpanan. Data yang diperoleh akan dikirimkan ke platform cloud Adafruit IO melalui protokol MQTT, di mana pengguna dapat mengaksesnya melalui aplikasi ponsel atau website.

Dengan sistem ini, pengguna dapat mengelola air secara lebih efisien, mencegah kebocoran, dan menerima notifikasi dini ketika air di tangki hampir habis. Sistem juga dapat diperluas untuk memantau beberapa titik pengukuran berbeda di rumah, seperti dapur atau kamar mandi, dengan menambahkan modul tambahan.

# Komponen
## 1. ESP32
ESP32 adalah Mikrokontroler System on Chip (SoC) berbiaya rendah dari Espressif Systems, yang juga sebagai pengembang dari SoC ESP8266 yang terkenal dengan NodeMCU. ESP32 adalah penerus SoC ESP8266 dengan menggunakan Mikroprosesor Xtensa LX6 32-bit Tensilica dengan Wi-Fi dan Bluetooth yang terintegrasi.
ESP32 memiliki dua prosesor komputasi, satu prosesor untuk mengelola jaringan WiFi dan Bluetooth, serta satu prosesor lainnya untuk menjalankan aplikasi. Dilengkapi dengan memori RAM yang cukup besar untuk menyimpan data. Fitur yang berguna seperti TCP/IP, HTTP, dan FTP.
Pada proyek ini ESP32 berfungsi sebagai pusat pengendali yang mengumpulkan data dari sensor dan mengirimkannya ke sistem monitoring.

## 2. Sensor Ultrasonic
Sensor ultrasonik merupakan sensor yang menggunakan gelombang ultrasonik. Gelombang ultrasonik yaitu gelombang yang umum digunakan untuk mendeteksi keberadaan suatu benda dengan memperkirakan jarak antara sensor dan benda tersebut. Sensor ini berfungsi untuk mengubah besaran fisis (bunyi) menjadi besaran listrik begitu pula sebaliknya. Gelombang ultrasonik memiliki frekuensi sebesar 20.000 Hz. Bunyi tersebut tidak dapat didengar oleh telinga manusia. Bunyi tersebut dapat didengar oleh hewan tertentu seperti anjing, kelelawar dan kucing. Bunyi gelombang ultrasonik dapat merambat melalui zat cair, padat dan gas. Benda cair merupakan media merambat yang paling baik untuk sensor ultrasonik jika dibandingkan dengan benda padat dan gas. 
Pada proyek ini sensor ultrasonic digunakan untuk mengukur ketinggian air dengan memantulkan gelombang suara ke permukaan air. 

## 3. Flow Sensor
Flow sensor merupakan sensor yang digunakan untuk mengukur aliran cairan seperti gas atau cairan. Flow sensor memanfaatkan sub sistem mekanik dan listrik untuk mengukur perubahan atribut fisik fluida dan menghitung alirannya. Mengukur atribut fisik tergantung pada atribut fluida. Fluida gas, cair dan non-newtonian memiliki perilaku satu sama lain yang sangat berbeda sehingga metode yang digunakan untuk mengukur alirannya juga harus berbeda. Flow sensor bisa dibagi menjadi dua jenis, yaitu contact sensor dan non-contact sensor. Flow contact sensor digunakan dalam aplikasi dimana cairan atau gas yang diukur diperkirakan tidak akan tersumbat di dalam pipa ketika bersentuhan dengan bagian sensor yang bergerak. Sedangkan flow non-contact sensor tidak memiliki bagian yang bergerak dan biasanya digunakan ketika cairan atau gas yang dipantau akan terkontaminasi maupun diubah secara fisik serta bersentuhan dengan bagian yang bergerak. 
Pada proyek ini flow sensor berfungsi untuk mengukur aliran air yang mengalir dalam pipa.

## 4. Adaptor 12V 2A
Adaptor 12V 2A adalah sebuah alat yang digunakan untuk mengubah sumber daya listrik dari AC (arus bolak-balik) ke DC (arus searah), dengan output 12 volt dan kemampuan untuk memberikan arus hingga 2 ampere. Adaptor ini sering digunakan untuk perangkat elektronik seperti router, CCTV, dan berbagai peralatan lainnya yang membutuhkan sumber daya 12V DC. Adaptor 12V 2A digunakan untuk menyediakan daya yang stabil dengan tegangan 12V dan arus 2A. Komponen seperti solenoid valve dan relay membutuhkan daya ini untuk beroperasi. Adaptor memastikan sistem mendapatkan tegangan yang diperlukan tanpa gangguan.

## 5. Solenoid Valve
Solenoid valve adalah katup yang dikendalikan oleh arus AC atau DC melalui coil/selenoida. Katup Solenoid adalah elemen control yang paling sering digunakan dalam sistem fluida. Seperti pada sistem pneumatic, sistem hidrolik atau sistem control mesin memerlukan elemen control otomatis. Katup ini bisa dikendalikan oleh ESP32 untuk membuka atau menutup aliran sesuai kebutuhan.
Solenoid valve akan beroperasi jika coil/kumparan menerima tegangan arus yang sesuai dengan tegangan operasi (kebanyakan tegangan kerja katup solenoid adalah 100/200 VAC dan sebagian besar tegangan operasi pada tegangan DC adalah 12/24 VDC). Dan sebuah pin akan tertarik akibat gaya magnet yang dihasilkan oleh kumparan solenoid. Dan saat pin sitarik ke atas, cairan akan mengalir dengan cepat dari rongga C ke bagian D. Oleh karena itu, tekanan di rongga C berkurang dan tekanan cairan yang masuk akan menaikkan diafragma. Biarkan katup utama terbuka dan cairan mengalir langsung dari A ke F.

## 6. Modul Relay
Modul relay Arduino adalah perangkat keras yang berfungsi untuk mengontrol perangkat listrik eksternal seperti motor, lampu dan peralatan rumah tangga lainnya menggunakan platform Arduino. Modul ini terdiri dari relay dan beberapa komponen pendukung lainnya yang terintegrasi dengan papan sirkuit terpadu (PCB). Sedangkan relay adalah saklar elektronik yang dapat dikontrol secara elektrik. Ketika relay diberikan sinyal listrik, kontaknya akan terbuka atau tertutup, sehingga memungkinkan arus listrik mengalir atau terputus. Pada umumnya, modul relay ini terhubung ke papan Arduino melalui pin digital.
Modul Relay memungkinkan ESP32 mengontrol perangkat tegangan tinggi dengan aman, seperti solenoid valve atau pompa air, melalui sinyal dari mikrokontroler.

# Diagram Arsitektur
<div align="center">
    <img src="https://github.com/oreo240202/AQUASMART/blob/77f9cb3edbcd3e97788744c1c1b3db2177442cfd/versibaru.drawio%20(1).png" alt="Gambar"width="600">
</div>

# Tim Pengembang
<div align="center">
    <img src="https://github.com/user-attachments/assets/0372e012-ae6d-4ac8-b26e-02273f16eb6d" alt="STRUKTUR AQUA SMART" width="400">
</div>

# Timeline Pengembangan

| Minggu | Tugas                                           | Tanggal                   |
|--------|-------------------------------------------------|---------------------------|
| 1      | Perencanaan dan pengajuan proposal              | 01-10-2024 s/d 07-10-2024 |
| 2      | Pengembangan hardware dan pemrograman ESP32     | 08-10-2024 s/d 14-10-2024 |
| 3      | Pengujian sistem IoT dan integrasi cloud        | 15-10-2024 s/d 21-10-2024 |
| 4      | Finalisasi dan presentasi proyek                | 22-10-2024 s/d 04-11-2024 |


# Rincian Pengeluaran Biaya

| Item                       | Jumlah | Harga Satuan (Rp) | Total (Rp) |
|---------------------------|--------|-------------------|------------|
| ESP32                     | 1      | 75,000            | 75,000     |
| Sensor Ultrasonic         | 1      | 10,000            | 10,000     |
| Flow Sensor              | 1      | 74,000            | 74,000     |
| Adaptor 12V 2A            | 1      | 16,000            | 16,000     |
| Solenoid Valve              | 1      | 65,000            | 65,000     |
| Modul Relay               | 2      | 8,200            | 16,400     |
| Kabel-Kabel               | 1      | 10,000            | 10,000     |
| Cetak 3D                 | 1      | 200,000                 | 200,000           |
| **Total Biaya**          | -      | -                 | **466,400**|


# Hardware
## 1. SCHEMATIC RANGKAIAN
Berikut ini adalah hasil skematik rangkaian sistem monitoring air menggunakan software Kicad
<div align="center">
    <img src="https://github.com/oreo240202/AQUASMART/blob/main/Hardware/Desain_PCB/SCHEMATIC_V2.jpeg" alt="SCHEMATIC RANGKAIAN" width="500">
</div>

## 2. DESAIN PCB
Berikut ini adalah hasil layout rangkaian sistem monitoring air menggunakan software Kicad
<div align="center">
    <img src="https://github.com/oreo240202/AQUASMART/blob/main/Hardware/Desain_PCB/LAYOUT_V2.jpeg" alt="DESAIN PCB" width="500">
</div>

## 3. 3D MODEL PCB
Berikut ini adalah hasil 3D rangkaian sistem monitoring air menggunakan software Kicad
<div align="center">
    <img src="https://github.com/oreo240202/AQUASMART/blob/main/Hardware/Desain_PCB/3D_V2.jpeg" alt="3D MODEL PCB" width="500">
</div>

# Software

## 1. FLOWCHART
<div align="center">
    <img src="https://github.com/user-attachments/assets/4fdbddaa-5829-4554-b1dc-bb49611a2188" alt="image" width="500">
</div>

## 2. Simulasi Wokwi
<div align="center">
    <img src="https://github.com/oreo240202/AQUASMART/blob/main/Software/ESP32_Source_Code/Rangkaian_Wokwi.jpeg?raw=true" alt="Simulasi Wokwi" width="500">
</div>

Link : https://wokwi.com/projects/411618765119428609

## 3. NODE-RED
<div align="center">
    <img src="https://raw.githubusercontent.com/2122600021-ALFARRUQ/AQUASMART/refs/heads/Website/Diagram/node_red_flow.png" alt="Simulasi Wokwi" width="500">
</div>

## 4. SEQUENCE DIAGRAM
<div align="center">
    <img src="https://github.com/2122600021-ALFARRUQ/AQUASMART/blob/3778b2f44b3d93d860f37e5c0d14aa3951c5bfdd/Diagram/squance.png?raw=true" alt="SEQUENCE DIAGRAM" width="500">
</div>

## 5. CLASS DIAGRAM
<div align="center">
    <img src="https://github.com/2122600021-ALFARRUQ/AQUASMART/blob/main/Diagram/class.png?raw=true" alt="CLASS DIAGRAM" width="500">
</div>

# Dokumentasi

## 1. Video Percobaan Pengiriman Data dari ESP32 ke Broker MQTT
https://github.com/user-attachments/assets/0b649f9e-3a0d-4be2-93d4-879152762dc5 
## 2. Video Simulasi Wokwi
https://github.com/user-attachments/assets/3788917b-d15c-42b3-9d15-79d57b5753b3 
## 3. Video Simulasi Aplikasi
### 3.1 Video Simulasi Aplikasi Web
https://github.com/user-attachments/assets/d782f18b-91e5-41b1-a5a1-bee070e43c8c
### 3.2 Video Simulasi Aplikasi Mobile
https://github.com/user-attachments/assets/036225ad-1f3f-4121-946e-6db940966c42
## 4. Video Pengujian Sensor Ultrasonik
https://github.com/user-attachments/assets/7d10899d-bf8c-4fc1-9f14-af5eacd0cc40 
## 5. Video Pengujian Hardware
https://github.com/user-attachments/assets/dedbf46f-3d43-4d81-ba96-16eca15a14ef
## 6. Video Penggunaan Alat
Link : https://drive.google.com/drive/folders/1OPCK6A9JROWr-ocdMjcz_6QO9YeVU3Sy
## 7. Proses Pengerjaan
<p align="center">
  <img src="https://github.com/user-attachments/assets/b48404d0-b90c-4dd7-b640-3d69c6e4e424" alt="Image 1" width="200">
  <img src="https://github.com/user-attachments/assets/93b567e6-60e9-42d6-a9c2-8a759874346b" alt="Image 2" width="200">
  <img src="https://github.com/user-attachments/assets/d0b173b4-0548-4b1a-8c1d-f2d03dced3e8" alt="Image 3" width="200">
</p>
<p align="center">
  <img src="https://github.com/user-attachments/assets/b8ea3627-333c-4b8a-a423-c07887acc34b" alt="Image 4" width="200">
  <img src="https://github.com/user-attachments/assets/104cba61-26aa-4e5f-aec0-28c381f2a529" alt="Image 5" width="200">
</p>

## 8. Video Pengiklanan 
https://github.com/user-attachments/assets/52b6b247-8677-437f-991a-c6e8a309753d 
## 9. Video Presentasi
https://github.com/user-attachments/assets/3ab094f8-9b1d-4ff9-a2a7-7a724e087a73


