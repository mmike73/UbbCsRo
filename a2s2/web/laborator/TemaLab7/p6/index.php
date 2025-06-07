<?php

session_start();
require_once __DIR__ . '/db.php';

$article = null;
$approved_comments = [];
$error_message = '';
$success_message = '';

if (!$mysqli || $mysqli->connect_errno) {
    die('MySQL connection is not open!');
}

try {
    $stmt_article = $mysqli->prepare("SELECT id, title, content, created_at FROM articles WHERE id = 1");
    if ($stmt_article) {
        $stmt_article->execute();
        $result_article = $stmt_article->get_result();
        if ($result_article->num_rows == 1) {
            $article = $result_article->fetch_assoc();
        } else {
            $error_message = "Articolul nu a fost găsit.";
        }
        $stmt_article->close();
    } else {
        throw new Exception("Eroare la pregătirea interogării articolului: " . $mysqli->error);
    }
} catch (Exception $e) {
    error_log($e->getMessage());
    $error_message = "A apărut o problemă la încărcarea articolului.";
}

function generateCsrfToken() {
    if (empty($_SESSION['csrf_token'])) {
        $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
    }
    return $_SESSION['csrf_token'];
}

function verifyCsrfToken($token) {
    return isset($_SESSION['csrf_token']) && hash_equals($_SESSION['csrf_token'], $token);
}


if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['action']) && $_POST['action'] == 'post_comment') {
    if (!isset($_POST['csrf_token']) || !verifyCsrfToken($_POST['csrf_token'])) {
        $error_message = "Eroare de securitate: Cerere invalidă (CSRF).";
        error_log("Tentativă CSRF detectată de la IP: " . $_SERVER['REMOTE_ADDR']);
    } else {
        $article_id = $article['id'] ?? null; // ID-ul articolului la care se postează
        $author_name = trim($_POST['author_name'] ?? '');
        $comment_text = trim($_POST['comment_text'] ?? '');

        if (empty($article_id) || empty($author_name) || empty($comment_text)) {
            $error_message = "Numele și comentariul sunt obligatorii.";
        } else {
            try {
                $stmt_insert = $mysqli->prepare("INSERT INTO comments (article_id, author_name, comment_text, is_approved) VALUES (?, ?, ?, FALSE)");
                if ($stmt_insert) {
                    $stmt_insert->bind_param("iss", $article_id, $author_name, $comment_text);
                    if ($stmt_insert->execute()) {
                        $success_message = "Comentariul tău a fost trimis și va fi afișat după aprobare.";
                    } else {
                        throw new Exception("Eroare la adăugarea comentariului: " . $stmt_insert->error);
                    }
                    $stmt_insert->close();
                } else {
                    throw new Exception("Eroare la pregătirea interogării de inserare comentariu: " . $mysqli->error);
                }
            } catch (Exception $e) {
                error_log($e->getMessage());
                $error_message = "A apărut o problemă la postarea comentariului. Vă rugăm să încercați mai târziu.";
            }
        }
    }
}

if ($article) {
    try {
        $stmt_comments = $mysqli->prepare("SELECT author_name, comment_text, posted_at FROM comments WHERE article_id = ? AND is_approved = TRUE ORDER BY posted_at DESC");
        if ($stmt_comments) {
            $stmt_comments->bind_param("i", $article['id']);
            $stmt_comments->execute();
            $result_comments = $stmt_comments->get_result();
            while ($row = $result_comments->fetch_assoc()) {
                $approved_comments[] = $row;
            }
            $stmt_comments->close();
        } else {
            throw new Exception("Eroare la pregătirea interogării comentariilor: " . $mysqli->error);
        }
    } catch (Exception $e) {
        error_log($e->getMessage());
        $error_message = "A apărut o problemă la încărcarea comentariilor.";
    }
}

$csrf_token = generateCsrfToken();

$mysqli->close();
?>
<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?php echo $article ? htmlspecialchars($article['title']) : 'Articol'; ?></title>
    <link rel="stylesheet" href="p6.css">
</head>
<body>
    <div class="container">
        <nav>
            <ul>
                <li><a href="index.php">Articol și Comentarii</a></li>
                <li><a href="admin_login.php">Autentificare Administrator</a></li>
            </ul>
        </nav>

        <?php if ($article) { ?>
            <article>
                <h1><?php echo htmlspecialchars($article['title']); ?></h1>
                <p class="article-date">Publicat la: <?php echo htmlspecialchars($article['created_at']); ?></p>
                <div class="article-content">
                    <?php echo nl2br(htmlspecialchars($article['content'])); ?>
                </div>
            </article>

            <hr>

            <h2>Postează un Comentariu</h2>
            <?php if (!empty($success_message)) { ?>
                <p class="success-message"><?php echo htmlspecialchars($success_message); ?></p>
            <?php } ?>
            <?php if (!empty($error_message)) { ?>
                <p class="error-message"><?php echo htmlspecialchars($error_message); ?></p>
            <?php } ?>

            <form action="index.php" method="POST">
                <input type="hidden" name="action" value="post_comment">
                <input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars($csrf_token); ?>">

                <div class="form-group">
                    <label for="author_name">Numele Tău:</label>
                    <input type="text" id="author_name" name="author_name" required aria-label="Numele autorului comentariului">
                </div>
                <div class="form-group">
                    <label for="comment_text">Comentariul Tău:</label>
                    <textarea id="comment_text" name="comment_text" rows="5" required aria-label="Textul comentariului"></textarea>
                </div>
                <button type="submit">Postează Comentariu</button>
            </form>

            <hr>

            <h2>Comentarii Aprobate</h2>
            <div class="comments-section">
                <?php if (!empty($approved_comments)) { ?>
                    <?php foreach ($approved_comments as $comment) { ?>
                        <div class="comment-item">
                            <p class="comment-author"><strong><?php echo htmlspecialchars($comment['author_name']); ?></strong> <span class="comment-date">pe <?php echo htmlspecialchars($comment['posted_at']); ?></span></p>
                            <p><?php echo nl2br(htmlspecialchars($comment['comment_text'])); ?></p>
                        </div>
                    <?php } ?>
                <?php } else { ?>
                    <p>Nu există comentarii aprobate încă. Fii primul care postează!</p>
                <?php } ?>
            </div>

        <?php } else { ?>
            <p class="error-message">Articolul nu poate fi afișat.</p>
        <?php } ?>
    </div>
</body>
</html>