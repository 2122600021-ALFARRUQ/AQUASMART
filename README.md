![flyer](https://github.com/user-attachments/assets/6e9112aa-8cb3-4763-a0f8-a7f793d0ec59)

# AQUA SMART
<div align="center">
    <img src="https://github.com/user-attachments/assets/5526e358-7520-43ce-8ac9-127eed4594b0" alt="AQUA SMART Logo" width="200">
</div>

# Daftar Isi

- [Deskripsi](#deskripsi)
- [Komponen](#komponen)
   * [ESP32](#1-esp32)
   * [Sensor Ultrasonic](#2-sensor-ultrasonic)
   * [Flow Sensor](#3-flow-sensor)
   * [Adaptor 12V 2A](#4-adaptor-12v-2a)
   * [Solenoid Valve](#5-solenoid-valve)
   * [Modul Relay](#6-modul-relay)
- [Diagram Arsitektur](#diagram-arsitektur)
- [Tim Pengembang](#tim-pengembang)
- [Timeline Pengembangan](#timeline-pengembangan)
- [Estimasi Biaya](#estimasi-biaya)
- [Hardware](#hardware)
  * [Schematic Rangkaian](#1-schematic-rangkaian)
  * [Desain PCB](#2-desain-pcb)
  * [3D Model PCB](#3-3d-model-pcb)
- [Software](#software)
  * [Flowchart](#1-flowchart)
  * [Simulasi Wokwi](#2-simulasi-wokwi) 
- [Video Aplikasi](#video-aplikasi)
- [Video Pengujian Sensor Ultrasonik](#video-pengujian-sensor-ultrasonik)
- [Spesifikasi Produk](#spesifikasi-produk)
- [Petunjuk Penggunaan](petunjuk-Penggunaan)

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
    <img src="https://github.com/oreo240202/AQUASMART/blob/77f9cb3edbcd3e97788744c1c1b3db2177442cfd/versibaru.drawio%20(1).png" alt="Gambar">
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
| 4      | Finalisasi dan presentasi proyek                | 22-10-2024 s/d 28-10-2024 |


# Estimasi Biaya

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
    <img src="https://github.com/oreo240202/AQUASMART/blob/main/Software/ESP32_Source_Code/Flowchart_Program_ESP32.svg?raw=true" alt="FLOWCHART" width="500">
</div>

## 2. Simulasi Wokwi
<div align="center">
    <img src="https://github.com/oreo240202/AQUASMART/blob/main/Software/ESP32_Source_Code/Rangkaian_Wokwi.jpeg?raw=true" alt="Simulasi Wokwi" width="500">
</div>

Link : https://wokwi.com/projects/411618765119428609

## 3. NODE-RED
<div align="center">
    <img src="https://raw.githubusercontent.com/2122600021-ALFARRUQ/AQUASMART/UI/UX-Design/Design_nodered.png" alt="FLOWCHART" width="500">
</div>

# Dokumentasi

https://github.com/user-attachments/assets/3788917b-d15c-42b3-9d15-79d57b5753b3 

# Video Aplikasi
(https://github.com/user-attachments/assets/bdbf62a1-ba29-4b3a-aca4-8215bf1cfdcd)

# Video Pengujian Sensor Ultrasonik

https://github.com/user-attachments/assets/7d10899d-bf8c-4fc1-9f14-af5eacd0cc40 

# Spesifikasi Produk

# Petunjuk Penggunaan

