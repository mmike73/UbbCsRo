<?php
session_start();
$conn = new mysqli("localhost", "root", "", "php");
if ($conn->connect_error) die("Eroare conexiune");

if (isset($_POST['username'], $_POST['parola'])) {
    $u = $_POST['username'];
    $p = $_POST['parola'];

    $stmt = $conn->prepare("SELECT id FROM utilizatori WHERE username = ? AND parola = ? AND activat = 1");
    $stmt->bind_param("ss", $u, $p);
    $stmt->execute();
    $stmt->store_result();

    if ($stmt->num_rows === 1) {
        $_SESSION['user'] = $u;
        echo "Autentificare reusita";
    } else {
        echo "Date incorecte sau cont neactivat";
    }
}
?>

<form method="post">
    Username: <input type="text" name="username" required><br>
    Parola: <input type="password" name="parola" required><br>
    <button type="submit">Autentificare</button>
</form>
