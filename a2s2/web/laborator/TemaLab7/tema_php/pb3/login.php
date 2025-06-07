<?php
session_start();

$host = 'localhost';
$user = 'root';
$pass = '';
$dbname = 'php';

$conn = new mysqli($host, $user, $pass, $dbname);
if ($conn->connect_error) {
    die('Eroare conexiune DB');
}
$conn->set_charset('utf8');

if (isset($_POST['username']) && isset($_POST['parola'])) {
    $username = trim($_POST['username']);
    $parola = trim($_POST['parola']);

    $stmt = $conn->prepare("SELECT id, parola FROM profesori WHERE username = ?");
    $stmt->bind_param("s", $username);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows === 1) {
        $user = $result->fetch_assoc();
        if ($user['parola'] === $parola) {
            $_SESSION['profesor_id'] = $user['id'];
            header('Location: admin.php');
            exit;
        } else {
            echo "Parola incorecta.";
        }
    } else {
        echo "Utilizator inexistent.";
    }
}
?>

<form method="post">
    Username: <input type="text" name="username" required><br>
    Parola: <input type="password" name="parola" required><br>
    <button type="submit">Autentificare</button>
</form>
