<?php
$con = mysqli_connect("localhost", "root", "", "as_db");

$dataHistory = mysqli_query($con, "SELECT * FROM tandon ORDER BY id DESC LIMIT 10");
$timeLabels = [];
$capacityData = [];
$flowRateData = [];

while ($row = mysqli_fetch_assoc($dataHistory)) {
    $timeLabels[] = $row['time'];
    $capacityData[] = $row['kapasitas'];
    $flowRateData[] = $row['flowRate'];
}

$timeLabels = array_reverse($timeLabels);
$capacityData = array_reverse($capacityData);
$flowRateData = array_reverse($flowRateData);

$latestData = mysqli_query($con, "SELECT pumpState, solenoidState FROM tandon ORDER BY id DESC LIMIT 1");
$d = mysqli_fetch_object($latestData);

echo json_encode([
    'timeLabels' => $timeLabels,
    'capacityData' => $capacityData,
    'flowRateData' => $flowRateData,
    'pumpState' => $d->pumpState,
    'solenoidState' => $d->solenoidState
]);
?>
