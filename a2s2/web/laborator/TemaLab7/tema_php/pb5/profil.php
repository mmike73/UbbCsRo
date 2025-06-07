<?php
session_start();
$conn = new mysqli("localhost","root","","php");
if($conn->connect_error) die("Eroare conexiune");

if(!isset($_GET['id'])) die("Nu s-a specificat user");

$id = (int)$_GET['id'];
$stmt = $conn->prepare("SELECT username FROM users WHERE id = ?");
$stmt->bind_param("i", $id);
$stmt->execute();
$res = $stmt->get_result();
if($res->num_rows === 0) die("User inexistent");
$user = $res->fetch_assoc();

echo "<h1>Profilul lui " . htmlspecialchars($user['username']) . "</h1>";

$stmt2 = $conn->prepare("SELECT id, filename FROM poze WHERE user_id = ?");
$stmt2->bind_param("i", $id);
$stmt2->execute();
$res2 = $stmt2->get_result();

while($row = $res2->fetch_assoc()) {
    echo "<div>";
    echo "<img src='uploads/" . htmlspecialchars($row['filename']) . "' width='150'>";
    if(isset($_SESSION['user_id']) && $_SESSION['user_id'] === $id) {
        echo " <a href='sterge.php?id=" . $row['id'] . "' onclick='return confirm(\"Stergi poza?\");'>Sterge</a>";
    }
    echo "</div>";
}
