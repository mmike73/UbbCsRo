<?php

session_start();
require_once __DIR__ . '/db.php';

$error_message = '';

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = trim($_POST['username'] ?? '');
    $password = trim($_POST['password'] ?? '');

    if (empty($username) || empty($password)) {
        $error_message = "both fields are required";
    } else {
        $stmt = $mysqli->prepare("SELECT id, username, password_hash, name FROM administrators WHERE username = ?");
        if ($stmt) {
            $stmt->bind_param("s", $username);
            $stmt->execute();
            $result = $stmt->get_result();

            if ($result->num_rows == 1) {
                $admin = $result->fetch_assoc();
                if ($password == $admin['password_hash']) {
                    $_SESSION['admin_id'] = $admin['id'];
                    $_SESSION['admin_username'] = $admin['username'];
                    $_SESSION['admin_name'] = $admin['name'];

                    header("Location: admin_dashboard.php");
                    exit();
                } else {
                    $error_message = "wrong username or passwd";
                }
            } else {
                $error_message = "wrong username or passwd";
            }
            $stmt->close();
        } else {
            error_log("query preparation error: " . $mysqli->error);
            $error_message = "internal error";
        }
    }
}
$mysqli->close();
?>
<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>admin auth</title>
</head>
<body>
    <div class="container">
        <h1>admin auth</h1>

        <nav>
            <ul>
                <li><a href="index.php">auth and comments</a></li>
                <li><a href="admin_login.php">admin auth</a></li>
            </ul>
        </nav>

        <?php if (!empty($error_message)) { ?>
            <p class="error-message"><?php echo htmlspecialchars($error_message); ?></p>
        <?php } ?>

        <form action="admin_login.php" method="POST">
            <div class="form-group">
                <label for="username">Nume Utilizator:</label>
                <input type="text" id="username" name="username" required aria-label="admin user">
            </div>
            <div class="form-group">
                <label for="password">Parolă:</label>
                <input type="password" id="password" name="password" required aria-label="admin passwd">
            </div>
            <button type="submit">Autentificare</button>
        </form>
    </div>
</body>
</html>