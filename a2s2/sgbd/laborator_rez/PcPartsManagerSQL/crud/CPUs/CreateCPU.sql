CREATE PROCEDURE createCPU
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
AS
BEGIN
    DECLARE @Errors NVARCHAR(MAX);

    SET @Errors = dbo.validateCPU(
        @manufacturerId,
        @model,
        @baseClock,
        @boostClock,
        @socket,
        @noCores,
        @noThreads,
        @fabricationTechnologyNM,
        @powerW,
        @price
    );

    IF LEN(@Errors) > 0
    BEGIN
        RAISERROR(@Errors, 16, 1);
        RETURN;
    END

    INSERT INTO CPUs (
        manufacturerId,
        model,
        baseClock,
        boostClock,
        socket,
        noCores,
        noThreads,
        fabricationTehnologyNm,
        powerW,
        price
    )
    VALUES (
        @manufacturerId,
        @model,
        @baseClock,
        @boostClock,
        @socket,
        @noCores,
        @noThreads,
        @fabricationTechnologyNM,
        @powerW,
        @price
    );

    PRINT 'CPU successfully created.';
END;
