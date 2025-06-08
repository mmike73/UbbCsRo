DECLARE @manufacturerId INT, 
        @model VARCHAR(100), 
        @type VARCHAR(100), 
        @stickFormat VARCHAR(100), 
        @sizeGb SMALLINT, 
        @configuration VARCHAR(100), 
        @frequency SMALLINT, 
        @latency VARCHAR(100), 
        @price SMALLINT;

-- Insert 100 unique RAM entries
DECLARE @counter INT = 1;
WHILE @counter <= 100
BEGIN
    -- Randomly assign manufacturer and attributes
    SET @manufacturerId = CASE 
        WHEN RAND() < 0.33 THEN 35013 
        WHEN RAND() < 0.66 THEN 35014 
        ELSE 35015 
    END;

    SET @type = CASE 
        WHEN RAND() < 0.5 THEN 'DDR4' 
        WHEN RAND() < 0.8 THEN 'DDR5' 
        ELSE 'DDR3' 
    END;

    SET @stickFormat = CASE 
        WHEN RAND() < 0.8 THEN 'DIMM' 
        ELSE 'SODIMM' 
    END;

    SET @sizeGb = CASE 
        WHEN RAND() < 0.5 THEN 8 
        WHEN RAND() < 0.8 THEN 16 
        ELSE 32 
    END;

    SET @configuration = CASE 
        WHEN @sizeGb = 32 THEN 'Quad Channel' 
        WHEN RAND() < 0.7 THEN 'Dual Channel' 
        ELSE 'Single Channel' 
    END;

    SET @frequency = CASE 
        WHEN @type = 'DDR5' THEN 4000 + FLOOR(RAND() * 2000) -- DDR5: 4000-6000 MHz
        WHEN @type = 'DDR4' THEN 2400 + FLOOR(RAND() * 1600) -- DDR4: 2400-4000 MHz
        ELSE 1333 + FLOOR(RAND() * 533) -- DDR3: 1333-1866 MHz
    END;

    SET @latency = CASE 
        WHEN @type = 'DDR5' THEN 'CL' + CAST(36 + FLOOR(RAND() * 10) AS VARCHAR) 
        WHEN @type = 'DDR4' THEN 'CL' + CAST(14 + FLOOR(RAND() * 6) AS VARCHAR) 
        ELSE 'CL' + CAST(9 + FLOOR(RAND() * 3) AS VARCHAR) 
    END;

    SET @price = FLOOR(20 + RAND() * 980); -- Price between $20 and $1000

    SET @model = CONCAT(
        CASE @manufacturerId 
            WHEN 35013 THEN 'Corsair '
            WHEN 35014 THEN 'Kingston '
            ELSE 'Samsung ' 
        END, 
        'Model-', @counter);

    -- Call the stored procedure
    EXEC createRAM 
        @manufacturerId, 
        @model, 
        @type, 
        @stickFormat, 
        @sizeGb, 
        @configuration, 
        @frequency, 
        @latency, 
        @price;

    -- Increment counter
    SET @counter = @counter + 1;
END;
GO
