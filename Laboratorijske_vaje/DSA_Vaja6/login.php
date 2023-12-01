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
    <h1>Prijava</h1>

    
    <form action="/index.php" method="post">
        Username: <input type="text" name="user"><br>
        Password: <input type="password" name="pass"><br>
        <button type="submit">Prijava</button>
    </form>

</body>
</html>