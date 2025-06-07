<?php
session_start();
$conn = new mysqli("localhost","root","","php");
if($conn->connect_error) die("Eroare conexiune");

if(isset($_POST['username'], $_POST['parola'])) {
    $u = trim($_POST['username']);
    $p = trim($_POST['parola']);
    $stmt = $conn->prepare("SELECT id, parola FROM users WHERE username = ?");
    $stmt->bind_param("s", $u);
    $stmt->execute();
    $rez = $stmt->get_result();
    if($rez->num_rows === 1) {
        $user = $rez->fetch_assoc();
        if(password_verify($p, $user['parola'])) {
            $_SESSION['user_id'] = $user['id'];
            $_SESSION['username'] = $u;
            header("Location: profil.php?id=" . $user['id']);
            exit;
        }
    }
    echo "Date invalide";
}
?>
<form method="post">
    <input name="username" required>
    <input name="parola" type="password" required>
    <button type="submit">Autentifica-te</button>
</form>
