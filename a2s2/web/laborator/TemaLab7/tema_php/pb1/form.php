<?php session_start(); ?>
<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Cautare Trenuri</title>
</head>
<body>
    <form action="cauta_trenuri.php" method="post">
        <label>Localitate plecare:</label>
        <input type="text" name="plecare" required>

        <label>Localitate sosire:</label>
        <input type="text" name="sosire" required>

        <label>
            <input type="checkbox" name="legatura" value="1">
            Permite curse cu legatura
        </label>
        <!-- Token CSRF -->
        <input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars(session_id()); ?>">
        <input type="submit" value="Cauta">
    </form>
</body>
</html>
