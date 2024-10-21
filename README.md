# <div align="center">Project PBL Jaringan Sensor</div>
### <div align="center">Prodi Elektronika - PENS</div>

## <div align="center">Dosen Pengampu</div>
<div align="center">
Akhmad Hendriawan, ST, MT <br>
NIP: 197501272002121003
</div>


# AQUA SMART
![AQUA SMART (1)](https://github.com/user-attachments/assets/5526e358-7520-43ce-8ac9-127eed4594b0)

# WSN-PBL_IOT-Home-Water-Monitoring
Sistem Monitoring Penggunaan Air Berbasis IoT ini dirancang untuk membantu rumah tangga dalam memantau penggunaan dan ketersediaan air secara real-time. Menggunakan ESP32 sebagai kontroler utama, sistem ini memanfaatkan sensor aliran air (Flow Sensor) untuk melacak jumlah air yang digunakan serta sensor ultrasonik untuk mengukur level air di dalam tangki penyimpanan. Data yang diperoleh akan dikirimkan ke platform cloud Adafruit IO melalui protokol MQTT, di mana pengguna dapat mengaksesnya melalui aplikasi ponsel atau website.

Dengan sistem ini, pengguna dapat mengelola air secara lebih efisien, mencegah kebocoran, dan menerima notifikasi dini ketika air di tangki hampir habis. Sistem juga dapat diperluas untuk memantau beberapa titik pengukuran berbeda di rumah, seperti dapur atau kamar mandi, dengan menambahkan modul tambahan.

# Daftar Isi

- [Diagram Arsitektur](#diagram-arsitektur)
- [Tim Pengembang](#tim-pengembang)
- [Timeline Pengembangan](#timeline-pengembangan)
- [Estimasi Biaya](#estimasi-biaya)
- [Hardware](#hardware)
- [Software](#software)
- [Spesifikasi Produk](#spesifikasi-produk)
- [Petunjuk Penggunaan](petunjuk-Penggunaan)

# Diagram Arsitektur
![alt text](https://github.com/oreo240202/AQUASMART/blob/77f9cb3edbcd3e97788744c1c1b3db2177442cfd/versibaru.drawio%20(1).png)


# Tim Pengembang

| Nama                   | Nrp                          | Jobdesk                  |
|-----------------------|--------------------------------|------------------------|
| Al Farruq R. A.      | 2122600021                      |   Project Manager      |
| Farrel Juan M.       | 2122600015                        |    Hardware Developer  |
| M. Rizqi Atmajaya    | 2122600025                      |  Project Tester        |
| Owen Pratama S.      |  2122600018                     |    Software Developer  |
| Aisyah                |  2122600027                    |  Data Analyst          |
| Rheza Firmansyah      | 2122600014                       | UX/UI Designer         |

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
SCHEMATIC RANGKAIAN
![alt text](https://github.com/oreo240202/AQUASMART/blob/main/Hardware/Desain_PCB/Schematic.jpg?raw=true)

DESAIN PCB

![alt text](https://github.com/oreo240202/AQUASMART/blob/main/Hardware/Desain_PCB/Desain_PCB.jpg?raw=true)

3D MODEL PCB

![alt text](https://github.com/oreo240202/AQUASMART/blob/main/Hardware/Desain_PCB/aquasmart_3D_PCB.png?raw=true)
# Software
## FLOWCHART
![alt text](https://github.com/oreo240202/AQUASMART/blob/main/Software/ESP32_Source_Code/Flowchart_Program_ESP32.svg?raw=true)

## Simulasi Wokwi 
![alt text](https://github.com/oreo240202/AQUASMART/blob/main/Software/ESP32_Source_Code/Rangkaian_Wokwi.jpeg?raw=true)

Link : https://wokwi.com/projects/411618765119428609

# Dokumentasi
Link : https://youtu.be/5Tg6bV3kbho

# Spesifikasi Produk

# Petunjuk Penggunaan

