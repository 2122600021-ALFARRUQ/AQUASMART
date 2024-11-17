<!doctype html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>AQUA SMART</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet"
    integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script> <!-- Add jQuery for AJAX -->
</head>

<body>
<div class="container text-center">
    <img src="AQUA.png" style="width: 300px">
    <h2>Sistem Monitoring Penggunaan Air</h2>

    <div class="container text-center mt-3">
      <div class="row align-items-start">
        <div class="col">
          <div class="card">
            <div class="card-header" style="background-color: red; color: white;">
              <h3>KAPASITAS</h3>
            </div>
            <div class="card-body">
              <canvas id="capacityChart" width="400" height="200"></canvas>
            </div>
          </div>
        </div>

        <div class="col">
          <div class="card">
            <div class="card-header" style="background-color: blue; color: white;">
              <h3>FLOW RATE</h3>
            </div>
            <div class="card-body">
              <canvas id="flowRateChart" width="400" height="200"></canvas>
            </div>
          </div>
        </div>
      </div>
    </div>

    <div class="row align-items-start mt-3">
        <div class="col">
          <div class="card">
            <div class="card-header" style="background-color: green; color: white;">
              <h3>PUMP STATE</h3>
            </div>
            <div class="card-body">
              <h1 id="pumpState" style="font-size: 100px">Loading...</h1>
            </div>
          </div>
        </div>

        <div class="col">
          <div class="card">
            <div class="card-header" style="background-color: purple; color: white;">
              <h3>SOLENOID STATE</h3>
            </div>
            <div class="card-body">
              <h1 id="solenoidState" style="font-size: 100px">Loading...</h1>
            </div>
          </div>
        </div>
      </div>
</div>

<script>
  const ctxCapacity = document.getElementById('capacityChart').getContext('2d');
  const ctxFlowRate = document.getElementById('flowRateChart').getContext('2d');
  
  let capacityChart = new Chart(ctxCapacity, {
    type: 'line',
    data: { labels: [], datasets: [{ label: 'Kapasitas (L)', data: [], borderColor: 'red', fill: false }] }
  });

  let flowRateChart = new Chart(ctxFlowRate, {
    type: 'line',
    data: { labels: [], datasets: [{ label: 'Flow Rate (L/min)', data: [], borderColor: 'blue', fill: false }] }
  });

  function fetchData() {
    $.ajax({
      url: 'fetch_data.php', // Separate PHP file that returns JSON data for charts and states
      type: 'GET',
      success: function(data) {
        const parsedData = JSON.parse(data);
        
        capacityChart.data.labels = parsedData.timeLabels;
        capacityChart.data.datasets[0].data = parsedData.capacityData;
        capacityChart.update();

        flowRateChart.data.labels = parsedData.timeLabels;
        flowRateChart.data.datasets[0].data = parsedData.flowRateData;
        flowRateChart.update();

        document.getElementById('pumpState').textContent = parsedData.pumpState ? 'Hidup' : 'Mati';
        document.getElementById('solenoidState').textContent = parsedData.solenoidState ? 'Hidup' : 'Mati';
      }
    });
  }

  // Auto-refresh every 5 seconds
  setInterval(fetchData, 5000);
</script>

<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"
  integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
</body>

</html>
