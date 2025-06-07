<?php
header('Content-Type: application/json');
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: POST, GET, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");

if ($_SERVER['REQUEST_METHOD'] == 'OPTIONS') {
    exit(0);
}

try {
    $input = json_decode(file_get_contents('php://input'), true) ?? $_POST;
    
    $board = $input['board'] ?? array_fill(0, 9, "");
    $player = $input['player'] ?? "X";
    
    if (!is_array($board) || count($board) !== 9) {
        throw new Exception("Invalid board structure");
    }

    function checkWin($b, $sym) {
        $wins = [
            [0,1,2],[3,4,5],[6,7,8], 
            [0,3,6],[1,4,7],[2,5,8],  
            [0,4,8],[2,4,6]   
        ];
        foreach ($wins as $w) {
            if ($b[$w[0]] === $sym && $b[$w[1]] === $sym && $b[$w[2]] === $sym) {
                return true;
            }
        }
        return false;
    }

    function computerMove($b) {
        $empty = array_keys(array_filter($b, function($cell) { return $cell === ""; }));
        if (!empty($empty)) {
            $b[$empty[array_rand($empty)]] = "O";
        }
        return $b;
    }

    $response = ['board' => $board, 'status' => ''];
    
    if (checkWin($board, "X")) {
        $response['status'] = "You win!";
    } else {
        $board = computerMove($board);
        $response['board'] = $board;
        
        if (checkWin($board, "O")) {
            $response['status'] = "Computer wins!";
        } elseif (!in_array("", $board, true)) {
            $response['status'] = "Draw!";
        }
    }
    
    echo json_encode($response);
    
} catch (Exception $e) {
    http_response_code(400);
    echo json_encode(['error' => $e->getMessage()]);
}
?>