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

switch ($action) {
    case 'get_filters':
        try {
            $manufacturers = $pdo->query("SELECT DISTINCT manufacturer as name FROM products WHERE manufacturer IS NOT NULL")->fetchAll();
            $processors = $pdo->query("SELECT DISTINCT processor as name FROM products WHERE processor IS NOT NULL")->fetchAll();
            $memories = $pdo->query("SELECT DISTINCT memory as name FROM products WHERE memory IS NOT NULL")->fetchAll();
            $storages = $pdo->query("SELECT DISTINCT storage as name FROM products WHERE storage IS NOT NULL")->fetchAll();
            $videoCards = $pdo->query("SELECT DISTINCT video_card as name FROM products WHERE video_card IS NOT NULL")->fetchAll();
            
            echo json_encode([
                'manufacturers' => $manufacturers ?: [],
                'processors' => $processors ?: [],
                'memories' => $memories ?: [],
                'storages' => $storages ?: [],
                'videoCards' => $videoCards ?: []
            ]);
        } catch (PDOException $e) {
            echo json_encode(['error' => 'Database query failed: ' . $e->getMessage()]);
        }
        break;
        
    case 'get_products':
        try {
            $manufacturer = $_GET['manufacturer'] ?? null;
            $processor = $_GET['processor'] ?? null;
            $memory = $_GET['memory'] ?? null;
            $storage = $_GET['storage'] ?? null;
            $videoCard = $_GET['video_card'] ?? null;
            
            $query = "SELECT * FROM products WHERE 1=1";
            $params = [];
            
            if ($manufacturer && $manufacturer !== '') {
                $query .= " AND manufacturer = ?";
                $params[] = $manufacturer;
            }
            
            if ($processor && $processor !== '') {
                $query .= " AND processor = ?";
                $params[] = $processor;
            }
            
            if ($memory && $memory !== '') {
                $query .= " AND memory = ?";
                $params[] = $memory;
            }
            
            if ($storage && $storage !== '') {
                $query .= " AND storage = ?";
                $params[] = $storage;
            }
            
            if ($videoCard && $videoCard !== '') {
                $query .= " AND video_card = ?";
                $params[] = $videoCard;
            }
            
            $stmt = $pdo->prepare($query);
            $stmt->execute($params);
            $products = $stmt->fetchAll();
            
            echo json_encode($products ?: []);
        } catch (PDOException $e) {
            echo json_encode(['error' => 'Database query failed: ' . $e->getMessage()]);
        }
        break;
        
    default:
        echo json_encode(['error' => 'Invalid action']);
}
?>