USE [pc_parts_manager];
GO

CREATE PROCEDURE versiune5
AS
BEGIN
	ALTER TABLE carcase
	ADD cod_sursa INT;

	ALTER TABLE carcase
	ADD CONSTRAINT sursa FOREIGN KEY (cod_sursa)
	REFERENCES surse(cod_sursa);
END;
GO

CREATE PROCEDURE undo_versiune5
AS
BEGIN
	ALTER TABLE carcase
	DROP CONSTRAINT sursa;

	ALTER TABLE carcase
	DROP COLUMN cod_sursa;
END;
GO

DROP PROCEDURE undo_versiune5;
GO

EXEC versiune5
EXEC undo_versiune5


SELECT CONSTRAINT_NAME
FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS
WHERE TABLE_NAME = 'carcase';


