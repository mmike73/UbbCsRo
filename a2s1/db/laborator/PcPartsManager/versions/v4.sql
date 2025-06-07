USE [pc_parts_manager];
GO

CREATE PROCEDURE versiune4
AS
BEGIN
	ALTER TABLE placi_video
	ADD TFLOPS FLOAT NULL;
END;
GO

CREATE PROCEDURE undo_versiune4
AS
BEGIN
	ALTER TABLE placi_video
	DROP COLUMN TFLOPS;
END;
GO

EXEC versiune4;
EXEC undo_versiune4;