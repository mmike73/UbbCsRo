USE [PcPartsManager]
GO

CREATE PROCEDURE insertIntoMotherboards
(@testId INT)
AS 
BEGIN
    DECLARE @i INT, @n INT;
    SET @i = 1;

    SELECT @n = NoOfRows FROM TestTables WHERE TestID = @testId;

    WHILE @i <= @n
    BEGIN
        DECLARE @motherboardId INT, @manufacturerId INT;

        SELECT @motherboardId = ISNULL(MAX(motherboardId), 0) + 1 FROM Motherboards;

        SELECT TOP 1 @manufacturerId = manufacturerId
        FROM Manufacturers
        ORDER BY NEWID();

        INSERT INTO Motherboards (
            manufacturerId, model, boardFormat, chipset, socket, ramType, 
            maximumMemorySize, pciEGeneration, integratedNetworkCard, bloetooth, price
        )
        VALUES (
            @manufacturerId,
            CONCAT('Model', @motherboardId),
            CASE WHEN @motherboardId % 2 = 0 THEN 'ATX' ELSE 'Micro ATX' END,
            CONCAT('Chipset', @motherboardId % 10 + 1),
            CONCAT('Socket', @motherboardId % 3 + 1),
            CASE WHEN @motherboardId % 2 = 0 THEN 'DDR4' ELSE 'DDR5' END,
            CASE WHEN @motherboardId % 3 = 0 THEN 64 ELSE 128 END,
            @motherboardId % 5 + 3.0,
            1,
            CASE WHEN @motherboardId % 2 = 0 THEN 1 ELSE 0 END,
            @motherboardId % 300 + 50
        );

        SET @i = @i + 1;
    END
END;
GO
