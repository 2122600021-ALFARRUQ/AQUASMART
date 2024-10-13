
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
- [Petunjuk Penggunaan](petunjuk-penggunaan)

# Diagram Arsitektur
![diagram arsitektur](https://github.com/user-attachments/assets/1f39079f-6660-4a60-ae13-af3b88021fef)

# Tim Pengembang

|No| Nama                   | Nrp                          | Jobdesk                  ||
|----------|-----------------------|--------------------------------|------------------------|---|
|1| Rheza Firmansyah      | 2122600014                       | UX/UI Designer         ||
|2| Farrel Juan M.       | 2122600015                        |    Hardware Developer  |
|3| Owen Pratama S.      |  2122600018                     |    Software Developer  |
|4| Al Farruq R. A.      | 2122600021                      |   Project Manager      |
|5| M. Rizqi Atmajaya    | 2122600025                      |  Project Tester        |
|6| Aisyah                |  2122600027                    |  Data Analyst          |


# Timeline Pengembangan
| Minggu | Tugas                                           | Tanggal                   |
|--------|-------------------------------------------------|---------------------------|
| 1      | Perencanaan dan pengajuan proposal              | 01-10-2024 s/d 07-10-2024 |
| 2      | Pengembangan hardware dan pemrograman ESP32     | 08-10-2024 s/d 14-10-2024 |
| 3      | Pengujian sistem IoT dan integrasi cloud        | 15-10-2024 s/d 21-10-2024 |
| 4      | Finalisasi dan presentasi proyek                | 22-10-2024 s/d 28-10-2024 |

# Estimasi Biaya

|No| Item                       | Jumlah | Harga Satuan (Rp) | Total (Rp) |
|-|---------------------------|--------|-------------------|------------|
|1| ESP32                     | 1      | 75,000            | 75,000     |
|2| Sensor Ultrasonic         | 1      | 10,000            | 10,000     |
|3| Liquid Flow Sensor 3/4 Inchi SEA               | 1      | 85,000            | 85,000     |
|4| Adaptor 5V 1A            | 1      | 20,000            | 20,000     |
|5| Kabel-Kabel               | 1      | 10,000            | 10,000     |
|6| Cetak 3D                 | 1      | 200,000                 | 200,000           |
|| **Total Biaya**          | -      | -                 | **400,000**|

# Hardware
SCHEMATIC RANGKAIAN
![alt text](https://github.com/oreo240202/AQUASMART/blob/main/Hardware%20/Desain%20PCB/Schematic.jpeg?raw=true)

DESAIN PCB

![alt text](https://github.com/oreo240202/AQUASMART/blob/main/Hardware%20/Desain%20PCB/Desain_PCB.jpeg?raw=true)

3D MODEL PCB

![alt text](https://github.com/oreo240202/AQUASMART/blob/main/Hardware%20/Desain%20PCB/aquasmart3d.jpg?raw=true)

# Software

FLOWCHART

![alt text](https://github.com/oreo240202/AQUASMART/blob/main/Software/Flowchart.jpeg?raw=true)

Simulasi Wokwi 

![alt text](https://github.com/oreo240202/AQUASMART/blob/main/Software/Rangkaian%20Wokwii.jpeg?raw=true)

Link : https://wokwi.com/projects/411618765119428609

# Spesifikasi Produk

# Petunjuk Penggunaan
