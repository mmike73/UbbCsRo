USE [PcPartsManager]
GO

CREATE PROCEDURE insertIntoCPUs
(@testId INT)
AS 
BEGIN
    DECLARE @i INT, @n INT;
    SET @i = 1;

    SELECT @n = NoOfRows FROM TestTables WHERE TestID = @testId;

    WHILE @i <= @n
    BEGIN
        DECLARE @cpuId INT, @manufacturerId INT;

        SELECT @cpuId = ISNULL(MAX(cpuId), 0) + 1 FROM CPUs;


        SELECT TOP 1 @manufacturerId = manufacturerId
        FROM Manufacturers
        ORDER BY NEWID();

        INSERT INTO CPUs (
            manufacturerId, model, baseClock, boostClock, socket, noCores, 
            noThreads, fabricationTehnologyNm, powerW, price
        )
        VALUES (
            @manufacturerId,
            CONCAT('Model', @cpuId),
            ROUND(2.5 + (@cpuId * 0.1), 1),
            ROUND(3.5 + (@cpuId * 0.1), 1),
            CONCAT('Socket', @cpuId % 3 + 1),
            @cpuId % 16 + 2,
            @cpuId % 32 + 4,
            @cpuId % 14 + 7,
            @cpuId % 100 + 50,
            @cpuId % 500 + 100
        );

        SET @i = @i + 1;
    END
END;
GO