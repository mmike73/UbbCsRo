CREATE PROCEDURE  createRAM
    @manufacturerId INT,
    @model VARCHAR(100),
    @type VARCHAR(100),
    @stickFormat VARCHAR(100),
    @sizeGb SMALLINT,
    @configuration VARCHAR(100),
    @frequency SMALLINT,
    @latency VARCHAR(100),
    @price SMALLINT
AS
BEGIN
    DECLARE @Errors NVARCHAR(MAX);

    SET @Errors = dbo.ValidateRAM(
        @manufacturerId,
        @model,
        @type,
        @stickFormat,
        @sizeGb,
        @configuration,
        @frequency,
        @latency,
        @price
    );

    IF LEN(@Errors) > 1
    BEGIN
        RAISERROR(@Errors, 16, 1);
        RETURN;
    END

    INSERT INTO RamMemory(
        manufacturerId,
        model,
        type,
        stickFormat,
        sizeGb,
        configuration,
        frequency,
        latency,
        price
    )
    VALUES (
        @manufacturerId,
        @model,
        @type,
        @stickFormat,
        @sizeGb,
        @configuration,
        @frequency,
        @latency,
        @price
    );

    PRINT 'RAM Memory successfully created.';
END;