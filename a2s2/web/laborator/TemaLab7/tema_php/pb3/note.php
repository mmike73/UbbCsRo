<?php
$conn = new mysqli('localhost', 'root', '', 'php');
if ($conn->connect_error) die('Eroare DB');
$conn->set_charset('utf8');

$studenti = $conn->query("SELECT * FROM studenti");

while ($student = $studenti->fetch_assoc()) {
    echo "<h3>" . htmlspecialchars($student['nume']) . "</h3>";
    $stmt = $conn->prepare("
        SELECT materii.nume AS materie, note.nota 
        FROM note 
        JOIN materii ON note.materie_id = materii.id
        WHERE note.student_id = ?
    ");
    $stmt->bind_param("i", $student['id']);
    $stmt->execute();
    $rez = $stmt->get_result();
    if ($rez->num_rows === 0) {
        echo "Nu exista note.<br>";
    } else {
        while ($row = $rez->fetch_assoc()) {
            echo htmlspecialchars($row['materie']) . ": " . $row['nota'] . "<br>";
        }
    }
}
?>
