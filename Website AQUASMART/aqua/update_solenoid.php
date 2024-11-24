<?php
// Konfigurasi database
$host = 'as-db.mysql.database.azure.com'; // Sesuaikan dengan host database Anda
$user = 'zwfvqusiix'; // Username database
$password = 'xKnW$jS1dx8SKF8S'; // Password database
$dbname = 'aquasmart-database'; // Nama database Anda

// Koneksi ke database
$conn = new mysqli($host, $user, $password, $dbname);

// Periksa koneksi
if ($conn->connect_error) {
    die("Koneksi gagal: " . $conn->connect_error);
}

// Ambil data dari request
$solenoidState = isset($_POST['solenoidState']) ? intval($_POST['solenoidState']) : 0;

// Update nilai di tabel tandon
$sql = "UPDATE solenoidstate SET solenoid_state = ? WHERE id = 1"; // Sesuaikan dengan struktur tabel Anda
$stmt = $conn->prepare($sql);
$stmt->bind_param("i", $solenoidState);

if ($stmt->execute()) {
    echo "Berhasil diperbarui";
} else {
    echo "Error: " . $stmt->error;
}

// Tutup koneksi
$stmt->close();
$conn->close();
?>
