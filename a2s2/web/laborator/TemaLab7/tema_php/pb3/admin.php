<?php
session_start();

if (!isset($_SESSION['profesor_id'])) {
    header('Location: login.php');
    exit;
}

$conn = new mysqli('localhost', 'root', '', 'php');
if ($conn->connect_error) die('Eroare DB');
$conn->set_charset('utf8');

if (isset($_POST['student_id'], $_POST['materie_id'], $_POST['nota'])) {
    $profesor_id = $_SESSION['profesor_id'];
    $student_id = intval($_POST['student_id']);
    $materie_id = intval($_POST['materie_id']);
    $nota = floatval($_POST['nota']);

    $stmt = $conn->prepare("INSERT INTO note (student_id, materie_id, profesor_id, nota) VALUES (?, ?, ?, ?) ON DUPLICATE KEY UPDATE nota = ?");
    $stmt->bind_param("iiiid", $student_id, $materie_id, $profesor_id, $nota, $nota);
    $stmt->execute();
}

$studenti = $conn->query("SELECT id, nume FROM studenti");
$materii = $conn->query("SELECT id, nume FROM materii");
?>

<form method="post">
    <label>Student:
        <select name="student_id" required>
            <?php while ($s = $studenti->fetch_assoc()): ?>
                <option value="<?= $s['id'] ?>"><?= htmlspecialchars($s['nume']) ?></option>
            <?php endwhile; ?>
        </select>
    </label><br>

    <label>Materie:
        <select name="materie_id" required>
            <?php while ($m = $materii->fetch_assoc()): ?>
                <option value="<?= $m['id'] ?>"><?= htmlspecialchars($m['nume']) ?></option>
            <?php endwhile; ?>
        </select>
    </label><br>

    <label>Nota:
        <input type="number" step="0.1" min="1" max="10" name="nota" required>
    </label><br>

    <button type="submit">Adauga/Modifica nota</button>
</form>
