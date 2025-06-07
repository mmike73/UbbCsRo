CREATE FUNCTION validateCPU (
    @manufacturerId INT,
    @model VARCHAR(100),
    @baseClock FLOAT,
    @boostClock FLOAT,
    @socket VARCHAR(100),
    @noCores SMALLINT,
    @noThreads SMALLINT,
    @fabricationTechnologyNM TINYINT,
    @powerW SMALLINT,
    @price SMALLINT
)
RETURNS NVARCHAR(MAX)
AS
BEGIN
    DECLARE @ErrorMessages NVARCHAR(MAX) = '';

    IF @manufacturerId IS NULL SET @ErrorMessages += 'Manufacturer ID cannot be NULL. ';
    IF @model IS NULL SET @ErrorMessages += 'Model cannot be NULL. ';
    IF @baseClock IS NULL SET @ErrorMessages += 'Base clock cannot be NULL. ';
    IF @boostClock IS NULL SET @ErrorMessages += 'Boost clock cannot be NULL. ';
    IF @socket IS NULL SET @ErrorMessages += 'Socket cannot be NULL. ';
    IF @noCores IS NULL SET @ErrorMessages += 'Number of cores cannot be NULL. ';
    IF @noThreads IS NULL SET @ErrorMessages += 'Number of threads cannot be NULL. ';
    IF @fabricationTechnologyNM IS NULL SET @ErrorMessages += 'Fabrication technology (nm) cannot be NULL. ';
    IF @powerW IS NULL SET @ErrorMessages += 'Power consumption cannot be NULL. ';
    IF @price IS NULL SET @ErrorMessages += 'Price cannot be NULL. ';

    IF LEN(@model) = 0 OR LEN(@model) > 100
        SET @ErrorMessages += 'Model name must be between 1 and 100 characters. ';
    IF @socket NOT IN ('LGA1200', 'LGA1700', 'AM4', 'AM5', 'TR4', 'sTRX4', 'LGA2066', 'LGA1151', 'LGA1155', 'LGA2011', 'LGA1366', 'LGA775')
        SET @ErrorMessages += 'Valid sockets: LGA1200, LGA1700, AM4, AM5, TR4, sTRX4, LGA2066, LGA1151, LGA1155, LGA2011, LGA1366, LGA775 ';

    IF dbo.existsManufacturerWithId(@manufacturerId) = 0
        SET @ErrorMessages += CONCAT('Manufacturer with id ', @manufacturerId, ' does not exist!');
    

    IF @baseClock <= 0 SET @ErrorMessages += 'Base clock must be a positive value. ';
    IF @boostClock <= 0 SET @ErrorMessages += 'Boost clock must be a positive value. ';
    IF @boostClock < @baseClock SET @ErrorMessages += 'Boost clock cannot be less than base clock. ';

    IF @noCores <= 0 OR @noCores > 256
        SET @ErrorMessages += 'Number of cores must be between 1 and 256. ';
    IF @noThreads <= 0 OR @noThreads > 512
        SET @ErrorMessages += 'Number of threads must be between 1 and 512. ';
    IF @fabricationTechnologyNM <= 0
        SET @ErrorMessages += 'Fabrication technology (nm) must be a positive value. ';
    IF @powerW <= 0 OR @powerW > 1000
        SET @ErrorMessages += 'Power consumption must be between 1 and 1000 watts. ';
    IF @price <= 0 OR @price > 100000
        SET @ErrorMessages += 'Price must be between 1 and 100,000. ';

    RETURN @ErrorMessages;
END;
