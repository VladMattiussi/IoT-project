<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css"/>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
    <!--<script src="script.js"></script>-->
    <title>Dashboard</title>
</head>
<body>
    <header>
        <h1>Smart Dumpster</h1>
    </header>
    <main>
        <section>
            <strong>Manual settings</strong>
            <form action="index.php" method="POST">
                <label for="available" name="available">Available</label>
                <input type="radio" name="state" value="available">
                <label for="unavailable" name="unavailable">Unavailable</label>
                <input type="radio" name="state" value="unavailable">
                <input type="submit" value="Submit">
            </form>
            <p>Lo stato è: 
                <?php
                        if(isset($_POST["state"])){
						$state = $_POST["state"];
                            echo "$state";
						$data = file_get_contents("dati.json");
						$data = json_decode($data,true);
						if($state == "available"){
						$data['db'][0]['state'] = "available";
						}
						if($state == "unavailable"){
						$data['db'][0]['state'] = "unavailable";
						}
						$new_data = json_encode($data);
						file_put_contents('dati.json', $new_data);
                        }
                ?>            
            </p>
            
            <strong>Check dati</strong>
            <form action="index.php" method="POST">
                <label for="show" name="show">Show</label>
                <input type="radio" name="show" value="show">
                <input type="submit" value="Submit">
            </form>
            <p>
            <?php
					 if(isset($_POST["show"])){
                            $data = file_get_contents("dati.json");
							$data = json_decode($data,true);
							print_r($data);
                        }
            ?>        
            </p>
        </section>
    </main>

</body>
</html>
