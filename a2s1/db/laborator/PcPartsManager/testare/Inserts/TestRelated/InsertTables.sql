USE [PcPartsManager];
GO

CREATE PROCEDURE insertIntoTables
(@tableName VARCHAR(50))
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM Tables WHERE Name = @tableName)
    BEGIN
        INSERT INTO Tables(Name)
        VALUES
        (@tableName)
    END
END;