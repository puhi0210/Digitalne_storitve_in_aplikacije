<?php
session_start();

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <h1>Moja stran</h1>

    <nav>
    <a href="">Domov</a>
    <a href="/login.php">Login</a>
    <a href="/logout.php">Logout</a>
    </nav>
    <?php
        
    if (isset($_SESSION["prijavljen"]) && isset($_SERVER["prijavljen"]) == true) {    
        echo"Prijavljeni ste! Pozdravljen $user";
    } else{

        if (isset($_POST["user"]) && isset($_POST["pass"])) {

            $user = $_POST["user"];
            $pass = $_POST["pass"];

            if (($user == "Miha") && ($pass == "123")) {
                echo"Prijavljeni ste! Pozdravljen $user";
                $_SESSION["prijavljen"] = true;
            } else{
                echo "Napačno ime ali geslo";
            }
        
        } else {
            echo "podatkov ni";
        }
    }

    ?>
</body>
</html>