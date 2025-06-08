CREATE PROCEDURE createMotherboard
    @manufacturerId INT,    
    @model VARCHAR(51), 
    @boardFormat VARCHAR(51), 
    @chipset VARCHAR(50), 
    @socket VARCHAR(50), 
    @ramType VARCHAR(10), 
    @maximumMemorySize SMALLINT, 
    @pciEGeneration FLOAT,
    @integratedNetworkCard BIT,
    @bloetooth BIT,
    @price SMALLINT
AS
BEGIN
    DECLARE @Errors NVARCHAR(MAX);

    SET @Errors = dbo.ValidateMotherboard(
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
        @price
    )

    IF LEN(@Errors) > 0
    BEGIN
        RAISERROR(@Errors, 16, 1);
        RETURN;
    END

    INSERT INTO Motherboards (
        manufacturerId,
        model,
        boardFormat,
        chipset,
        socket,
        ramType,
        maximumMemorySize,
        pciEGeneration,
        integratedNetworkCard,
        bloetooth,
        price
    )
    VALUES (
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
        @price
    )

    PRINT 'Motherboard successfully created.'
END