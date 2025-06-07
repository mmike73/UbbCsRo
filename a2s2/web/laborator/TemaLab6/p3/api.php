<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json");

$host = '127.0.0.1';
$db   = 'trenuri';
$user = 'badel';
$pass = 'badel';
$charset = 'utf8mb4';

$dsn = "mysql:host=$host;dbname=$db;charset=$charset";
$options = [
    PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
];

try {
    $pdo = new PDO($dsn, $user, $pass, $options);
} catch (PDOException $e) {
    die(json_encode(['error' => 'Database connection failed']));
}

$action = $_GET['action'] ?? '';

switch ($action) {
    case 'get_ids':
        $stmt = $pdo->query("SELECT id FROM records ORDER BY id");
        echo json_encode($stmt->fetchAll(PDO::FETCH_COLUMN, 0));
        break;
        
    case 'get_record':
        $id = $_GET['id'] ?? 0;
        $stmt = $pdo->prepare("SELECT * FROM records WHERE id = ?");
        $stmt->execute([$id]);
        echo json_encode($stmt->fetch() ?: ['error' => 'Record not found']);
        break;
        
    case 'save_record':
        $id = $_POST['id'] ?? 0;
        $name = $_POST['name'] ?? '';
        $email = $_POST['email'] ?? '';
        $status = $_POST['status'] ?? '';
        
        $stmt = $pdo->prepare("UPDATE records SET name = ?, email = ?, status = ? WHERE id = ?");
        $success = $stmt->execute([$name, $email, $status, $id]);
        
        echo json_encode(['success' => $success]);
        break;
        
    default:
        echo json_encode(['error' => 'Invalid action']);
}
?>