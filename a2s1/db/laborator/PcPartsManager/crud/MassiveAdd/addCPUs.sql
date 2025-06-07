/*INSERT INTO CPUs (manufacturerId, model, baseClock, boostClock, socket, noCores, noThreads, fabricationTehnologyNm, powerW, price)
VALUES 
INSERT INTO RamMemory (manufacturerId, model, type, stickFormat, sizeGb, configuration, frequency, latency, price)
VALUES 
INSERT INTO Motherboards (manufacturerId, model, boardFormat, chipset, socket, ramType, maximumMemorySize, pciEGeneration, integratedNetworkCard, bloetooth, price)
VALUES */

DECLARE @manufacturerId INT, 
        @model VARCHAR(100), 
        @baseClock FLOAT, 
        @boostClock FLOAT, 
        @socket VARCHAR(100), 
        @noCores SMALLINT, 
        @noThreads SMALLINT, 
        @fabricationTechnologyNM TINYINT, 
        @powerW SMALLINT, 
        @price SMALLINT;

-- Insert 100 unique CPUs
DECLARE @counter INT = 1;
WHILE @counter <= 100
BEGIN
    -- Randomly assign manufacturer and socket
    SET @manufacturerId = CASE 
        WHEN RAND() < 0.5 THEN 35007 
        ELSE 35008 
    END;

    SET @socket = CASE @manufacturerId 
        WHEN 35007 THEN (CASE WHEN RAND() < 0.5 THEN 'LGA1700' ELSE 'LGA1200' END)
        WHEN 35008 THEN 'AM4'
    END;

    -- Random model name
    SET @model = CONCAT(
        CASE @manufacturerId 
            WHEN 35007 THEN 'Intel Core '
            WHEN 35008 THEN 'AMD Ryzen ' 
        END, 
        'RandomModel', @counter);

    -- Random attributes
    SET @baseClock = ROUND(2.5 + RAND() * 2.5, 1);  -- Base clock between 2.5 and 5.0
    SET @boostClock = @baseClock + ROUND(RAND() * 1.5, 1); -- Boost clock higher than base
    SET @noCores = FLOOR(2 + RAND() * 14); -- Number of cores between 2 and 16
    SET @noThreads = @noCores * (1 + FLOOR(RAND() * 2)); -- Threads 1-2x cores
    SET @fabricationTechnologyNM = CASE 
        WHEN RAND() < 0.5 THEN 7 
        ELSE 10 
    END; -- Fabrication tech 7nm or 10nm
    SET @powerW = FLOOR(35 + RAND() * 90); -- Power between 35W and 125W
    SET @price = FLOOR(50 + RAND() * 950); -- Price between $50 and $1000

    -- Call stored procedure
    EXEC createCPU 
        @manufacturerId, 
        @model, 
        @baseClock, 
        @boostClock, 
        @socket, 
        @noCores, 
        @noThreads, 
        @fabricationTechnologyNM, 
        @powerW, 
        @price;

    -- Increment counter
    SET @counter = @counter + 1;
END;
GO
