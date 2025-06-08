USE [PcPartsManager];
GO

CREATE PROCEDURE updateCPUModel
    @id INT,
    @model VARCHAR(100)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @model IS NULL OR LEN(@model) = 0 OR LEN(@model) > 100
        RAISERROR('Model must be a non-empty string with a maximum length of 100 characters.', 16, 1);

    UPDATE CPUs
    SET model = @model
    WHERE cpuId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateCPUBaseClock
    @id INT,
    @val FLOAT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @val IS NULL OR @val <= 0
        RAISERROR('Base clock must be a positive value.', 16, 1);

    UPDATE CPUs
    SET baseClock = @val
    WHERE cpuId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateCPUBoostClock
    @id INT,
    @val FLOAT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @val IS NULL OR @val <= 0
        RAISERROR('Boost clock must be a positive value.', 16, 1);

    UPDATE CPUs
    SET boostClock = @val
    WHERE cpuId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateCPUSocket
    @id INT,
    @socket VARCHAR(100)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @socket IS NULL OR LEN(@socket) = 0 OR LEN(@socket) > 100
        RAISERROR('Socket must be a non-empty string with a maximum length of 100 characters.', 16, 1);

    UPDATE CPUs
    SET socket = @socket
    WHERE cpuId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateCPUNoCores
    @id INT,
    @val SMALLINT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @val IS NULL OR @val <= 0 OR @val > 256
        RAISERROR('Number of cores must be between 1 and 256.', 16, 1);

    UPDATE CPUs
    SET noCores = @val
    WHERE cpuId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateCPUNoThreads
    @id INT,
    @val SMALLINT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @val IS NULL OR @val <= 0 OR @val > 512
        RAISERROR('Number of threads must be between 1 and 512.', 16, 1);

    UPDATE CPUs
    SET noThreads = @val
    WHERE cpuId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO


CREATE PROCEDURE updateCPUPowerW
    @id INT,
    @val SMALLINT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @val IS NULL OR @val <= 0 OR @val > 1000
        RAISERROR('Power consumption must be between 1 and 1000 watts.', 16, 1);

    UPDATE CPUs
    SET powerW = @val
    WHERE cpuId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateCPUPrice
    @id INT,
    @val SMALLINT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @val IS NULL OR @val <= 0 OR @val > 100000
        RAISERROR('Price must be between 1 and 100,000.', 16, 1);

    UPDATE CPUs
    SET price = @val
    WHERE cpuId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO