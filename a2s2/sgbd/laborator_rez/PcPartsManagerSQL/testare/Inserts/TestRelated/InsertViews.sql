USE [PcPartsManager]
GO

CREATE PROCEDURE insertIntoViews
(@viewName VARCHAR(50))
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM Views WHERE Name = @viewName)
    BEGIN
        INSERT INTO Views(Name)
        VALUES
        (@viewName)
    END
END