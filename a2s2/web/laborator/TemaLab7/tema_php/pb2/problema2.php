<?php
session_start();

$n = isset($_POST['n']) ? (int)$_POST['n'] : 5;
if ($n <= 0) $n = 5;

$page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
if ($page <= 0) $page = 1;

$conn = new mysqli("localhost", "root", "", "php");
if ($conn->connect_error) {
    die("Eroare conexiune.");
}
$conn->set_charset("utf8");

$total_result = $conn->query("SELECT COUNT(*) as total FROM produse");
$total_row = $total_result->fetch_assoc();
$total = (int)$total_row['total'];

$start = ($page - 1) * $n;

$stmt = $conn->prepare("SELECT * FROM produse LIMIT ?, ?");
$stmt->bind_param("ii", $start, $n);
$stmt->execute();
$result = $stmt->get_result();

echo '<form method="post">';
echo 'Produse pe pagina: <select name="n" onchange="this.form.submit()">';
$options = [5,10,20,50];
foreach ($options as $opt) {
    $selected = ($opt == $n) ? ' selected' : '';
    echo "<option value='$opt'$selected>$opt</option>";
}
echo '</select>';
echo '</form>';

echo '<table border="1"><tr>';
while ($field = $result->fetch_field()) {
    echo "<th>" . htmlspecialchars($field->name) . "</th>";
}
echo '</tr>';

while ($row = $result->fetch_assoc()) {
    echo '<tr>';
    foreach ($row as $value) {
        echo '<td>' . htmlspecialchars($value) . '</td>';
    }
    echo '</tr>';
}
echo '</table>';

if ($page > 1) {
    $prev = $page - 1;
    echo "<a href='?page=$prev'>Anterior</a> ";
}
if ($start + $n < $total) {
    $next = $page + 1;
    echo "<a href='?page=$next'>Urmator</a>";
}

$conn->close();
?>
