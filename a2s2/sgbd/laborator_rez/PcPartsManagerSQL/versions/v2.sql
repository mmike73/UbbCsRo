USE [pc_parts_manager];
GO

CREATE PROCEDURE versiune2
AS
BEGIN
	ALTER TABLE memorie_ram
	ADD CONSTRAINT single_channel
	DEFAULT 'Single Channel' FOR configuratie
END;
GO

CREATE PROCEDURE undo_versiune2
AS
BEGIN
	ALTER TABLE memorie_ram 
	DROP CONSTRAINT single_channel;
END;
GO

EXEC versiune2;
EXEC undo_versiune2;

SELECT *
FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS
WHERE TABLE_NAME = 'memorie_ram' 
  AND CONSTRAINT_NAME = 'format_placute';

DROP PROCEDURE versiune2;
DROP PROCEDURE undo_versiune2;