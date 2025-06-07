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
    PDO::ATTR_EMULATE_PREPARES => false,
];

try {
    $pdo = new PDO($dsn, $user, $pass, $options);
} catch (PDOException $e) {
    die(json_encode(['error' => 'Database connection failed: ' . $e->getMessage()]));
}

$action = $_GET['action'] ?? '';
$offset = isset($_GET['offset']) ? (int)$_GET['offset'] : 0;
$limit = 3;

switch ($action) {
    case 'get_users':
        $stmt = $pdo->prepare("SELECT * FROM users LIMIT :limit OFFSET :offset");
        $stmt->bindParam(':limit', $limit, PDO::PARAM_INT);
        $stmt->bindParam(':offset', $offset, PDO::PARAM_INT);
        $stmt->execute();
        
        $users = $stmt->fetchAll();
        
        $countStmt = $pdo->query("SELECT COUNT(*) as total FROM users");
        $total = $countStmt->fetch()['total'];
        
        echo json_encode([
            'users' => $users,
            'hasNext' => ($offset + $limit) < $total,
            'hasPrev' => $offset > 0
        ]);
        break;
        
    default:
        echo json_encode(['error' => 'Invalid action']);
}
?>