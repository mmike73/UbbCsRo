USE [PcPartsManager];
GO

CREATE PROCEDURE insertIntoTtests
(@testName VARCHAR(50))
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM Tables WHERE Name = @testName)
    BEGIN
        INSERT INTO Tests(Name)
        VALUES
        (@testName)
    END
END;