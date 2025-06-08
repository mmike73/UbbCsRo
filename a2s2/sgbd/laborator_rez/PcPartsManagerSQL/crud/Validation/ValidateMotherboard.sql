CREATE FUNCTION validateMotherboard (
    @manufacturerId INT,
    @model VARCHAR(100),
    @boardFormat VARCHAR(100),
    @chipset VARCHAR(100),
    @socket VARCHAR(100),
    @ramType VARCHAR(100),
    @maximumMemorySize SMALLINT,
    @pciEGeneration FLOAT,
    @integratedNetworkCard BIT,
    @bluetooth BIT,
    @price SMALLINT
)
RETURNS NVARCHAR(MAX)
AS
BEGIN
    DECLARE @ErrorMessages NVARCHAR(MAX) = '';

    IF @manufacturerId IS NULL
        SET @ErrorMessages += 'Manufacturer ID cannot be NULL. ';
    ELSE IF dbo.existsManufacturerWithId(@manufacturerId) = 0
        SET @ErrorMessages += CONCAT('Manufacturer with ID ', @manufacturerId, ' does not exist. ');

    IF @model IS NULL OR LEN(@model) = 0 OR LEN(@model) > 51
        SET @ErrorMessages += 'Model must be between 1 and 50 characters. ';

    IF @boardFormat IS NULL OR @boardFormat NOT IN ('XT', 'AT', 'ATX', 'microATX', 'miniATX')
        SET @ErrorMessages += 'Valid board formats: XT, AT, ATX, microATX, miniATX  ';

    IF @chipset IS NULL OR LEN(@chipset) = 0 OR LEN(@chipset) > 50
        SET @ErrorMessages += 'Chipset must be between 1 and 50 characters. ';

    IF @socket IS NULL OR @socket NOT IN ('LGA1200', 'LGA1700', 'AM4', 'AM5', 'TR4', 'sTRX4', 'LGA2066', 'LGA1151', 'LGA1155', 'LGA2011', 'LGA1366', 'LGA775')
        SET @ErrorMessages += 'Valid sockets: LGA1200, LGA1700, AM4, AM5, TR4, sTRX4, LGA2066, LGA1151, LGA1155, LGA2011, LGA1366, LGA775 ';

    IF @ramType IS NULL OR @ramType NOT IN ('DDR', 'DDR2', 'DDR3', 'DDR4', 'DDR5')
        SET @ErrorMessages += 'Valid RAM types: DDR, DDR2, DDR3, DDR4, DDR5';

    IF @maximumMemorySize IS NULL OR @maximumMemorySize <= 0 OR @maximumMemorySize > 1024
        SET @ErrorMessages += 'Maximum memory size must be between 1 and 1024 GB. ';

    IF @pciEGeneration IS NULL OR @pciEGeneration <= 0
        SET @ErrorMessages += 'PCIe generation must be a positive value. ';

    IF @integratedNetworkCard NOT IN (0, 1)
        SET @ErrorMessages += 'Integrated network card must be 0 (false) or 1 (true). ';

    IF @bluetooth NOT IN (0, 1)
        SET @ErrorMessages += 'Bluetooth must be 0 (false) or 1 (true). ';

    IF @price IS NULL OR @price <= 0 OR @price > 100000
        SET @ErrorMessages += 'Price must be between 1 and 100,000. ';

    RETURN @ErrorMessages;
END;
GO
