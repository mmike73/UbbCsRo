<?php
require 'backend_conf.php';

$action = $_GET['action'] ?? '';

switch ($action) {
    case 'getDepartures':
        getDepartures();
        break;
    case 'getArrivals':
        $departure = $_GET['departure'] ?? '';
        if (!empty($departure)) {
            getArrivals($departure);
        } else {
            echo json_encode(['error' => 'Departure station not specified']);
        }
        break;
    default:
        echo json_encode(['error' => 'Invalid action']);
}

function getDepartures() {
    global $pdo;
    $stmt = $pdo->query("SELECT DISTINCT departure FROM routes ORDER BY departure");
    $departures = $stmt->fetchAll(PDO::FETCH_COLUMN, 0);
    echo json_encode($departures);
}

function getArrivals($departure) {
    global $pdo;
    $stmt = $pdo->prepare("SELECT arrival FROM routes WHERE departure = ? ORDER BY arrival");
    $stmt->execute([$departure]);
    $arrivals = $stmt->fetchAll(PDO::FETCH_COLUMN, 0);
    echo json_encode($arrivals);
}
?>