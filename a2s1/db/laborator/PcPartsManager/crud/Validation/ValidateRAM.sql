CREATE FUNCTION validateRAM (
    @manufacturerId INT,
    @model VARCHAR(100),
    @type VARCHAR(100),
    @stickFormat VARCHAR(100),
    @sizeGb SMALLINT,
    @configuration VARCHAR(100),
    @frequency SMALLINT,
    @latency VARCHAR(100),
    @price SMALLINT
)
RETURNS NVARCHAR(MAX)
AS
BEGIN
    DECLARE @ErrorMessages NVARCHAR(MAX) = '';

    -- Check for NULL values
    IF @manufacturerId IS NULL SET @ErrorMessages += 'Manufacturer ID cannot be NULL. ';
    IF @model IS NULL SET @ErrorMessages += 'Model cannot be NULL. ';
    IF @type IS NULL SET @ErrorMessages += 'Type cannot be NULL. ';
    IF @stickFormat IS NULL SET @ErrorMessages += 'Stick format cannot be NULL. ';
    IF @sizeGb IS NULL SET @ErrorMessages += 'Size in GB cannot be NULL. ';
    IF @configuration IS NULL SET @ErrorMessages += 'Configuration cannot be NULL. ';
    IF @frequency IS NULL SET @ErrorMessages += 'Frequency cannot be NULL. ';
    IF @latency IS NULL SET @ErrorMessages += 'Latency cannot be NULL. ';
    IF @price IS NULL SET @ErrorMessages += 'Price cannot be NULL. ';

    IF LEN(@model) = 0 OR LEN(@model) > 100
        SET @ErrorMessages += 'Model name must be between 1 and 100 characters. ';
    IF @type NOT IN ('DDR', 'DDR2', 'DDR3', 'DDR4', 'DDR5')
        SET @ErrorMessages += 'Valid RAM types: DDR, DDR2, DDR3, DDR4, DDR5 ';
    IF @stickFormat NOT IN ('DIMM', 'SO-DIMM')
        SET @ErrorMessages += 'Valid stick formats: DIMM, SO-DIMM ';
    IF LEN(@configuration) = 0 OR LEN(@configuration) > 100
        SET @ErrorMessages += 'Configuration must be between 1 and 100 characters. ';
    IF LEN(@latency) = 0 OR LEN(@latency) > 100
        SET @ErrorMessages += 'Latency must be between 1 and 100 characters. ';

    IF dbo.existsManufacturerWithId(@manufacturerId) = 0
        SET @ErrorMessages += CONCAT('Manufacturer with ID ', @manufacturerId, ' does not exist. ');

    IF @sizeGb <= 0 OR @sizeGb > 1024
        SET @ErrorMessages += 'Size in GB must be between 1 and 1024. ';
    IF @frequency <= 0 OR @frequency > 10000
        SET @ErrorMessages += 'Frequency must be between 1 and 10,000 MHz. ';
    IF @price <= 0 OR @price > 100000
        SET @ErrorMessages += 'Price must be between 1 and 100,000. ';

    RETURN @ErrorMessages;
END;
