<?php
$conn = new mysqli("localhost", "root", "", "php");
if ($conn->connect_error) die("Eroare conexiune");

if (isset($_GET['email'], $_GET['token'])) {
    $e = $_GET['email'];
    $t = $_GET['token'];

    $stmt = $conn->prepare("UPDATE utilizatori SET activat = 1 WHERE email = ? AND token = ?");
    $stmt->bind_param("ss", $e, $t);
    $stmt->execute();

    if ($stmt->affected_rows === 1) {
        echo "Cont activat";
    } else {
        echo "Date invalide";
    }
}
?>
