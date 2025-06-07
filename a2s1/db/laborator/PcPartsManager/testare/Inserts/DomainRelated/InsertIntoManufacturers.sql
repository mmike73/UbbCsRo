USE [PcPartsManager]
GO

CREATE PROCEDURE insertIntoManufacturers
    (@testId INT)
AS
BEGIN
    DECLARE @i INT, @n INT;
    SET @i = 1;

    SELECT @n = NoOfRows FROM TestTables WHERE TestID = @testId;

    WHILE @i <= @n
    BEGIN
        DECLARE @manufacturerId INT;
        SELECT @manufacturerId = ISNULL(MAX(manufacturerId), 0) + 1 FROM Manufacturers;

        INSERT INTO Manufacturers (name)
        VALUES
        (CONCAT('Manufacturer', @manufacturerId));

        SET @i = @i + 1;
    END
END;
GO
