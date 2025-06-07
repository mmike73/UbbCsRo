USE [PcPartsManager];
GO

CREATE PROCEDURE insertIntoTests
(@noTables INT, @noViews INT)
AS
BEGIN
    DECLARE @tableName VARCHAR(50);

	DECLARE table_cursor CURSOR FOR
	SELECT Name FROM Tables;

	OPEN table_cursor;

	FETCH NEXT FROM table_cursor INTO @tableName;

	WHILE @@FETCH_STATUS=0
	BEGIN
		IF NOT EXISTS (SELECT 1 FROM Tests WHERE CONCAT('Test',@tableName) = Name)
		BEGIN
			INSERT INTO Tests(Name)
			VALUES (CONCAT('Test',@tableName));
		END

		FETCH NEXT FROM table_cursor INTO @tableName;
	END

	CLOSE table_cursor;
	DEALLOCATE table_cursor;
END
