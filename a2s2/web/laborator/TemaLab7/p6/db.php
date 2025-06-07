<?php

define('DB_SERVER', 'localhost:3306');
define('DB_USERNAME', 'yourusername');
define('DB_PASSWORD', 'yourpassword');
define('DB_NAME', 'article_comments');

$mysqli = new mysqli(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);

if ($mysqli->connect_error) {
    error_log("Eroare de conectare la baza de date: " . $mysqli->connect_error);
    die("A apărut o problemă la conectarea la baza de date. Vă rugăm să încercați mai târziu.");
}
?>