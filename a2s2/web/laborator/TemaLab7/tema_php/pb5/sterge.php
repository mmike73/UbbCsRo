<?php
session_start();
$conn = new mysqli("localhost","root","","php");
if($conn->connect_error) die("Eroare conexiune");

if(!isset($_SESSION['user_id'])) die("Nu esti autentificat");
if(!isset($_GET['id'])) die("Nu s-a specificat poza");

$id_poze = (int)$_GET['id'];
$user_id = $_SESSION['user_id'];

$stmt = $conn->prepare("SELECT filename FROM poze WHERE id = ? AND user_id = ?");
$stmt->bind_param("ii", $id_poze, $user_id);
$stmt->execute();
$res = $stmt->get_result();
if($res->num_rows === 0) die("Poza nu exista sau nu ai drepturi");

$poza = $res->fetch_assoc();

unlink("uploads/" . $poza['filename']);

$stmt = $conn->prepare("DELETE FROM poze WHERE id = ?");
$stmt->bind_param("i", $id_poze);
$stmt->execute();

header("Location: profil.php?id=" . $user_id);
exit;
