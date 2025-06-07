<?php
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

require 'vendor/autoload.php';

$conn = new mysqli("localhost", "root", "", "php");
if ($conn->connect_error) die("Eroare conexiune");

if (isset($_POST['username'], $_POST['parola'], $_POST['email'])) {
    $u = trim($_POST['username']);
    $p = trim($_POST['parola']);
    $e = trim($_POST['email']);
    $token = bin2hex(random_bytes(16));

    $stmt = $conn->prepare("INSERT INTO utilizatori (username, parola, email, token) VALUES (?, ?, ?, ?)");
    $stmt->bind_param("ssss", $u, $p, $e, $token);
    $stmt->execute();

    $link = "http://localhost/tema_php/pb4/confirmare.php?email=$e&token=$token";

    $mail = new PHPMailer(true);
    try {
        $mail->isSMTP();
        $mail->Host       = 'smtp.gmail.com';
        $mail->SMTPAuth   = true;
        $mail->Username   = ''; // adresa Gmail reala
        $mail->Password   = '';    // parola de aplicatie (nu parola Gmail!)
        $mail->SMTPSecure = 'tls';
        $mail->Port       = 587;

        $mail->setFrom('', 'Site-ul Meu');
        $mail->addAddress($e);

        $mail->Subject = 'Confirmare cont';
        $mail->Body    = "Acceseaza linkul pentru confirmare: $link";

        $mail->send();
        echo "Verifica emailul pentru confirmare";
    } catch (Exception $ex) {
        echo "Eroare trimitere email: {$mail->ErrorInfo}";
    }
}
?>
