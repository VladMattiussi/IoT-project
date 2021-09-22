<?php if (isset($_GET['request'])):
		/*$dati = file_get_contents("./dati.json");
        header("application/json");*/
        
        $dati = file_get_contents("dati.json");
        $dati = json_decode($dati,true);

        $s = $dati['db'][0]['state'];
        //echo $s;
        if(strcmp($s, "available") == 0){
            echo 1; //available
        } else {
            echo 0; //not available
        }
		exit(1);
		endif;?>
<?php

if(isset($_GET["pollo"])){
    $a = $_GET["pollo"];
    echo $a;
}

if(isset($_GET["capacity"]) && isset($_GET["sleft"]) && isset($_GET["state"])){
    $a = $_GET["capacity"];
    $b = $_GET["sleft"];
    $st = $_GET["state"]; //1=available, else not avail


    var_dump($a);
    var_dump($b);

    $data = file_get_contents("dati.json");
    $data = json_decode($data,true);
    
    $data['db'][0]['capacity'] = $a;
    $data['db'][0]['spaceLeft'] = $b;
    if($st == 1){
        $data['db'][0]['state'] = "available";
    } else {
        $data['db'][0]['state'] = "unavailable";
    }

	$new_data = json_encode($data);
	file_put_contents('dati.json', $new_data);
}


?>