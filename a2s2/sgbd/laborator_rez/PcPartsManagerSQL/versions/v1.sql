USE [pc_parts_manager];
GO

CREATE PROCEDURE versiune1
AS
BEGIN
	ALTER TABLE placi_video
	ALTER COLUMN slot VARCHAR(50);
END;
GO

CREATE PROCEDURE undo_versiune1
AS
BEGIN
	ALTER TABLE placi_video
	ALTER COLUMN slot VARCHAR(10);
END;
GO

EXEC versiune1;
EXEC undo_versiune1;

