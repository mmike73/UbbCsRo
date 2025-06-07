<?php
session_start();

if (!isset($_POST['csrf_token']) || $_POST['csrf_token'] !== session_id()) {
    die("Acces neautorizat.");
}

$plecare = trim($_POST['plecare']);
$sosire = trim($_POST['sosire']);
$legatura = isset($_POST['legatura']);

$plecare_safe = htmlspecialchars($plecare);
$sosire_safe = htmlspecialchars($sosire);

$conn = new mysqli("localhost", "root", "", "trenuri");
if ($conn->connect_error) {
    die("Eroare conexiune.");
}
$conn->set_charset("utf8");

$stmt = $conn->prepare("SELECT * FROM trenuri WHERE loc_plecare = ? AND loc_sosire = ?");
$stmt->bind_param("ss", $plecare, $sosire);
$stmt->execute();
$rezultat = $stmt->get_result();

echo "<h2>Curse directe din $plecare_safe in $sosire_safe:</h2>";
if ($rezultat->num_rows === 0) {
    echo "<p>Niciun rezultat gasit.</p>";
}
while ($row = $rezultat->fetch_assoc()) {
    echo "<p>Plecare: {$row['loc_plecare']} la {$row['ora_plecare']} → Sosire: {$row['loc_sosire']} la {$row['ora_sosire']}</p>";
}

if ($legatura) {
    echo "<h2>Curse cu legatura din $plecare_safe in $sosire_safe:</h2>";
    $sql = "
        SELECT
            t1.loc_plecare AS plecare1, t1.loc_sosire AS legatura,
            t1.ora_plecare AS ora_plecare1, t1.ora_sosire AS ora_sosire1,
            t2.loc_plecare AS legatura2, t2.loc_sosire AS sosire2,
            t2.ora_plecare AS ora_plecare2, t2.ora_sosire AS ora_sosire2
        FROM trenuri t1
        JOIN trenuri t2 ON t1.loc_sosire = t2.loc_plecare
        WHERE t1.loc_plecare = ? AND t2.loc_sosire = ?
    ";
    $stmt2 = $conn->prepare($sql);
    $stmt2->bind_param("ss", $plecare, $sosire);
    $stmt2->execute();
    $rezultat2 = $stmt2->get_result();

    if ($rezultat2->num_rows === 0) {
        echo "<p>Nicio legatura gasita.</p>";
    }
    while ($row = $rezultat2->fetch_assoc()) {
        echo "<p>Prima etapa: {$row['plecare1']} → {$row['legatura']} (plecare la {$row['ora_plecare1']}, sosire la {$row['ora_sosire1']})<br>";
        echo "A doua etapa: {$row['legatura2']} → {$row['sosire2']} (plecare la {$row['ora_plecare2']}, sosire la {$row['ora_sosire2']})</p>";
    }
}

$conn->close();
