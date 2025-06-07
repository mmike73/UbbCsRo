<?php
session_start();
if(!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}
$conn = new mysqli("localhost","root","","php");
if($conn->connect_error) die("Eroare conexiune");

if(isset($_FILES['poza']) && $_FILES['poza']['error'] === 0) {
    $ext = strtolower(pathinfo($_FILES['poza']['name'], PATHINFO_EXTENSION));
    $allowed = ['jpg','jpeg','png','gif'];
    if(in_array($ext, $allowed)) {
        $nume_fisier = uniqid() . "." . $ext;
        $dest = "uploads/" . $nume_fisier;
        if(move_uploaded_file($_FILES['poza']['tmp_name'], $dest)) {
            $stmt = $conn->prepare("INSERT INTO poze(user_id, filename) VALUES (?, ?)");
            $stmt->bind_param("is", $_SESSION['user_id'], $nume_fisier);
            $stmt->execute();
            echo "Upload reusit";
        }
    }
}
?>
<form method="post" enctype="multipart/form-data">
    <input type="file" name="poza" required>
    <button type="submit">Incarca poza</button>
</form>
<a href="profil.php?id=<?php echo $_SESSION['user_id']; ?>">Profilul meu</a>
