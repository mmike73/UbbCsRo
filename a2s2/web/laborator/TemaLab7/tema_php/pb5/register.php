<?php
session_start();
$conn = new mysqli("localhost","root","","php");
if($conn->connect_error) die("Eroare conexiune");

if(isset($_POST['username'], $_POST['parola'])) {
    $u = trim($_POST['username']);
    $p = password_hash(trim($_POST['parola']), PASSWORD_DEFAULT);
    $stmt = $conn->prepare("INSERT INTO users(username, parola) VALUES (?, ?)");
    $stmt->bind_param("ss", $u, $p);
    if($stmt->execute()) {
        header("Location: login.php");
        exit;
    } else {
        echo "Eroare inregistrare";
    }
}
?>
<form method="post">
    <input name="username" required>
    <input name="parola" type="password" required>
    <button type="submit">Inregistreaza-te</button>
</form>
