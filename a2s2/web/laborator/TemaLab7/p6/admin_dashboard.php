<?php
// admin_dashboard.php - Tabloul de bord al administratorului

session_start();
require_once __DIR__ . '/db.php';

// Verifică autentificarea administratorului
if (!isset($_SESSION['admin_id'])) {
    header("Location: admin_login.php");
    exit();
}

$admin_id = $_SESSION['admin_id'];
$admin_name = $_SESSION['admin_name'];

$pending_comments = [];
$success_message = '';
$error_message = '';

// Functie pentru a genera un token CSRF
function generateCsrfToken() {
    if (empty($_SESSION['csrf_token'])) {
        $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
    }
    return $_SESSION['csrf_token'];
}

// Functie pentru a verifica token-ul CSRF
function verifyCsrfToken($token) {
    return isset($_SESSION['csrf_token']) && hash_equals($_SESSION['csrf_token'], $token);
}


// Procesează acțiunile (aprobare/ștergere)
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['action'])) {
    if (!isset($_POST['csrf_token']) || !verifyCsrfToken($_POST['csrf_token'])) {
        $error_message = "Eroare de securitate: Cerere invalidă (CSRF).";
        error_log("Tentativă CSRF detectată de la IP: " . $_SERVER['REMOTE_ADDR']);
    } else {
        $comment_id = filter_var($_POST['comment_id'] ?? null, FILTER_VALIDATE_INT);

        if ($comment_id === false || $comment_id === null) {
            $error_message = "ID comentariu invalid.";
        } else {
            try {
                if ($_POST['action'] == 'approve') {
                    $stmt_approve = $mysqli->prepare("UPDATE comments SET is_approved = TRUE, approved_by = ?, approved_at = CURRENT_TIMESTAMP WHERE id = ?");
                    if ($stmt_approve) {
                        $stmt_approve->bind_param("ii", $admin_id, $comment_id);
                        if ($stmt_approve->execute()) {
                            $success_message = "Comentariul a fost aprobat.";
                        } else {
                            throw new Exception("Eroare la aprobarea comentariului: " . $stmt_approve->error);
                        }
                        $stmt_approve->close();
                    } else {
                        throw new Exception("Eroare la pregătirea interogării de aprobare: " . $mysqli->error);
                    }
                } elseif ($_POST['action'] == 'delete') {
                    $stmt_delete = $mysqli->prepare("DELETE FROM comments WHERE id = ?");
                    if ($stmt_delete) {
                        $stmt_delete->bind_param("i", $comment_id);
                        if ($stmt_delete->execute()) {
                            $success_message = "Comentariul a fost șters.";
                        } else {
                            throw new Exception("Eroare la ștergerea comentariului: " . $stmt_delete->error);
                        }
                        $stmt_delete->close();
                    } else {
                        throw new Exception("Eroare la pregătirea interogării de ștergere: " . $mysqli->error);
                    }
                }
            } catch (Exception $e) {
                error_log($e->getMessage());
                $error_message = "A apărut o problemă la procesarea acțiunii. Vă rugăm să încercați mai târziu.";
            }
        }
    }
}

// Preluare comentarii în așteptare
try {
    $stmt_pending = $mysqli->prepare("SELECT c.id, c.author_name, c.comment_text, c.posted_at, a.title AS article_title
                                     FROM comments c
                                     JOIN articles a ON c.article_id = a.id
                                     WHERE c.is_approved = FALSE
                                     ORDER BY c.posted_at ASC");
    if ($stmt_pending) {
        $stmt_pending->execute();
        $result_pending = $stmt_pending->get_result();
        while ($row = $result_pending->fetch_assoc()) {
            $pending_comments[] = $row;
        }
        $stmt_pending->close();
    } else {
        throw new Exception("Eroare la pregătirea interogării comentariilor în așteptare: " . $mysqli->error);
    }
} catch (Exception $e) {
    error_log($e->getMessage());
    $error_message = "A apărut o problemă la încărcarea comentariilor în așteptare.";
}

// Generăm un nou token CSRF pentru afișarea formularului
$csrf_token = generateCsrfToken();

$mysqli->close();
?>
<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Tablou de Bord Administrator</title>
    <link rel="stylesheet" href="p6.css">
</head>
<body>
    <div class="container">
        <h1>Bun venit, Administrator <?php echo htmlspecialchars($admin_name); ?>!</h1>

        <nav>
            <ul>
                <li><a href="index.php">Articol și Comentarii</a></li>
                <li><a href="admin_dashboard.php">Tablou de Bord Administrator</a></li>
                <li><a href="logout.php">Delogare</a></li>
            </ul>
        </nav>

        <?php if (!empty($success_message)) { ?>
            <p class="success-message"><?php echo htmlspecialchars($success_message); ?></p>
        <?php } ?>
        <?php if (!empty($error_message)) { ?>
            <p class="error-message"><?php echo htmlspecialchars($error_message); ?></p>
        <?php } ?>

        <h2>Comentarii în Așteptare Aprobare</h2>
        <?php if (!empty($pending_comments)) { ?>
            <div class="comments-moderation">
                <?php foreach ($pending_comments as $comment) { ?>
                    <div class="comment-moderation-item">
                        <p><strong>Articol:</strong> <?php echo htmlspecialchars($comment['article_title']); ?></p>
                        <p class="comment-author"><strong>De la:</strong> <?php echo htmlspecialchars($comment['author_name']); ?> <span class="comment-date">pe <?php echo htmlspecialchars($comment['posted_at']); ?></span></p>
                        <p class="comment-text-moderation"><?php echo nl2br(htmlspecialchars($comment['comment_text'])); ?></p>
                        <form action="admin_dashboard.php" method="POST" style="display:inline;">
                            <input type="hidden" name="comment_id" value="<?php echo htmlspecialchars($comment['id']); ?>">
                            <input type="hidden" name="action" value="approve">
                            <input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars($csrf_token); ?>">
                            <button type="submit" class="approve-button">Aprobă</button>
                        </form>
                        <form action="admin_dashboard.php" method="POST" style="display:inline;" onsubmit="return confirm('Ești sigur că vrei să ștergi acest comentariu?');">
                            <input type="hidden" name="comment_id" value="<?php echo htmlspecialchars($comment['id']); ?>">
                            <input type="hidden" name="action" value="delete">
                            <input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars($csrf_token); ?>">
                            <button type="submit" class="delete-button">Șterge</button>
                        </form>
                    </div>
                <?php } ?>
            </div>
        <?php } else { ?>
            <p>Nu există comentarii în așteptare de aprobare.</p>
        <?php } ?>
    </div>
</body>
</html>