<?php
// Database connection
$host = "as-db.mysql.database.azure.com";
$user = "zwfvqusiix";
$password = "xKnW$jS1dx8SKF8S";
$database = "aquasmart-database";

$conn = new mysqli($host, $user, $password, $database);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT * FROM tandon";
$result = $conn->query(query: $sql);

$data = array();
if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        $data[] = $row;
    }
}

echo json_encode(value: $data);

$conn->close();
?>

<!--tampilan grafik-->
<div class="panel panel-primary">
    <div class="panel-heading">
        Grafik Data
    </div>

    <div class="panel-body">
        <!--canvas untuk grafik-->
        <canvas id="myChart"></canvas>

        <!--gambar grafik-->
        <script type="text/javascript">
            var canvas = document.getElementById('myChart');
            
            var data = {
                datasets : [{
                    label : "Air",
                    data : [
                        <?php
                        while($data_air = mysqli_fetch_array($data_air))
                        {
                            echo $data_air['air'].',';
                        }    
                        ?>
                    ]
                }]
            };

            //option grafik
            var option = {
                showLines : true,
                animation : {duration : 0}
            };

            //cetak grafik kedalam canvas
            var myLinesChart = Chart.Line(canvas, {
                data : data
            })
        </script>    
    </div>
</div>
