<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");


if ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
    http_response_code(200);
    exit();
}

$action = $_GET['action'] ?? '';
$path = $_GET['path'] ?? '';

$path = str_replace('..', '', $path);
$basePath = realpath('./'); 
$fullPath = realpath($basePath . DIRECTORY_SEPARATOR . $path);

if ($fullPath === false || strpos($fullPath, $basePath) !== 0) {
    die(json_encode(['error' => 'Access denied']));
}

switch ($action) {
    case 'list':
        listDirectory($fullPath, $path);
        break;
    case 'read':
        readFileContent($fullPath, $path);
        break;
    default:
        echo json_encode(['error' => 'Invalid action']);
}

function listDirectory($fullPath, $relativePath) {
    if (!is_dir($fullPath)) {
        echo json_encode(['error' => 'Not a directory']);
        return;
    }

    $items = scandir($fullPath);
    $directories = [];
    $files = [];

    foreach ($items as $item) {
        if ($item === '.' || $item === '..') continue;

        $itemPath = $fullPath . DIRECTORY_SEPARATOR . $item;
        $itemRelativePath = rtrim($relativePath, '/') . '/' . $item;

        if (is_dir($itemPath)) {
            $directories[] = [
                'name' => $item,
                'path' => $itemRelativePath,
                'type' => 'directory'
            ];
        } else {
            $files[] = [
                'name' => $item,
                'path' => $itemRelativePath,
                'type' => 'file',
                'size' => filesize($itemPath)
            ];
        }
    }

    usort($directories, fn($a, $b) => strcmp($a['name'], $b['name']));
    usort($files, fn($a, $b) => strcmp($a['name'], $b['name']));

    echo json_encode([
        'path' => $relativePath,
        'items' => array_merge($directories, $files)
    ]);
}

function readFileContent($fullPath, $relativePath) {
    if (!file_exists($fullPath)) {
        echo json_encode(['error' => 'File not found']);
        return;
    }

    if (is_dir($fullPath)) {
        echo json_encode(['error' => 'Path is a directory']);
        return;
    }

    $filename = basename($fullPath);
    $size = filesize($fullPath);
    $extension = strtolower(pathinfo($filename, PATHINFO_EXTENSION));

    $binaryExtensions = ['jpg', 'jpeg', 'png', 'gif', 'pdf', 'zip', 'exe', 'bin', ''];

    if (in_array($extension, $binaryExtensions)) {
        echo json_encode([
            'name' => $filename,
            'path' => $relativePath,
            'size' => $size,
            'isBinary' => true,
            'content' => 'Binary file content not displayed'
        ]);
        return;
    }

    $content = file_get_contents($fullPath);
    if ($content === false) {
        echo json_encode(['error' => 'Could not read file']);
        return;
    }

    echo json_encode([
        'name' => $filename,
        'path' => $relativePath,
        'size' => $size,
        'isBinary' => false,
        'content' => $content
    ]);
}
