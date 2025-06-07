DECLARE @manufacturerId INT, 
        @model VARCHAR(51), 
        @boardFormat VARCHAR(51), 
        @chipset VARCHAR(50), 
        @socket VARCHAR(50), 
        @ramType VARCHAR(10), 
        @maximumMemorySize SMALLINT, 
        @pciEGeneration FLOAT, 
        @integratedNetworkCard BIT, 
        @bloetooth BIT, 
        @price SMALLINT;

-- Insert 100 unique motherboards
DECLARE @counter INT = 1;
WHILE @counter <= 100
BEGIN
    -- Randomly assign manufacturer and attributes
    SET @manufacturerId = CASE 
        WHEN RAND() < 0.33 THEN 35010 
        WHEN RAND() < 0.5 THEN 35011 
        ELSE 35012 
    END;

    SET @boardFormat = CASE 
        WHEN RAND() < 0.5 THEN 'ATX' 
        ELSE 'Micro ATX' 
    END;

    SET @socket = CASE 
        WHEN @manufacturerId = 35010 THEN (CASE WHEN RAND() < 0.5 THEN 'LGA1700' ELSE 'LGA1200' END)
        WHEN @manufacturerId = 35011 THEN (CASE WHEN RAND() < 0.5 THEN 'AM4' ELSE 'LGA1151' END)
        ELSE (CASE WHEN RAND() < 0.5 THEN 'AM4' ELSE 'LGA1700' END)
    END;

    SET @chipset = CASE 
        WHEN @socket = 'LGA1700' THEN (CASE WHEN RAND() < 0.5 THEN 'Z690' ELSE 'B660' END)
        WHEN @socket = 'LGA1200' THEN (CASE WHEN RAND() < 0.5 THEN 'Z590' ELSE 'H510' END)
        WHEN @socket = 'AM4' THEN (CASE WHEN RAND() < 0.5 THEN 'B550' ELSE 'X570' END)
        ELSE 'A320' 
    END;

    SET @ramType = CASE 
        WHEN RAND() < 0.5 THEN 'DDR4' 
        ELSE 'DDR5' 
    END;

    SET @maximumMemorySize = CASE 
        WHEN @ramType = 'DDR5' THEN 128 
        ELSE 64 
    END;

    SET @pciEGeneration = CASE 
        WHEN @ramType = 'DDR5' THEN 5.0 
        ELSE 3.0 + FLOOR(RAND() * 2.0) 
    END;

    SET @integratedNetworkCard = CASE 
        WHEN RAND() < 0.8 THEN 1 
        ELSE 0 
    END;

    SET @bloetooth = CASE 
        WHEN RAND() < 0.6 THEN 1 
        ELSE 0 
    END;

    SET @price = FLOOR(50 + RAND() * 950); -- Price between $50 and $1000

    SET @model = CONCAT(
        CASE @manufacturerId 
            WHEN 35010 THEN 'Asus '
            WHEN 35011 THEN 'Gigabyte '
            ELSE 'MSI ' 
        END, 
        'RandomBoard', @counter);

    -- Call the stored procedure
    EXEC createMotherboard 
        @manufacturerId, 
        @model, 
        @boardFormat, 
        @chipset, 
        @socket, 
        @ramType, 
        @maximumMemorySize, 
        @pciEGeneration, 
        @integratedNetworkCard, 
        @bloetooth, 
        @price;

    -- Increment counter
    SET @counter = @counter + 1;
END;
GO
