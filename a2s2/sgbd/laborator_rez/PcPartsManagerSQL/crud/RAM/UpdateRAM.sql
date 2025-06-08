USE [PcPartsManager];
GO

CREATE PROCEDURE updateRAMManufacturerId
    @id INT,
    @manufacturerId INT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @manufacturerId IS NULL OR @manufacturerId <= 0
        RAISERROR('Manufacturer ID must be a positive integer.', 16, 1);

    UPDATE RamMemory
    SET manufacturerId = @manufacturerId
    WHERE ramId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateRAMModel
    @id INT,
    @model VARCHAR(100)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @model IS NULL OR LEN(@model) = 0 OR LEN(@model) > 100
        RAISERROR('Model must be a non-empty string with a maximum length of 100 characters.', 16, 1);

    UPDATE RamMemory
    SET model = @model
    WHERE ramId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateRAMType
    @id INT,
    @type VARCHAR(100)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @type IS NULL OR LEN(@type) = 0 OR LEN(@type) > 100
        RAISERROR('Type must be a non-empty string with a maximum length of 100 characters.', 16, 1);

    UPDATE RamMemory
    SET type = @type
    WHERE ramId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateRAMStickFormat
    @id INT,
    @stickFormat VARCHAR(100)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @stickFormat IS NULL OR LEN(@stickFormat) = 0 OR LEN(@stickFormat) > 100
        RAISERROR('Stick format must be a non-empty string with a maximum length of 100 characters.', 16, 1);

    UPDATE RamMemory
    SET stickFormat = @stickFormat
    WHERE ramId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateRAMSizeGB
    @id INT,
    @sizeGb SMALLINT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @sizeGb IS NULL OR @sizeGb <= 0 OR @sizeGb > 1024
        RAISERROR('Size in GB must be between 1 and 1024.', 16, 1);

    UPDATE RamMemory
    SET sizeGb = @sizeGb
    WHERE ramId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateRAMConfiguration
    @id INT,
    @configuration VARCHAR(100)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @configuration IS NULL OR LEN(@configuration) = 0 OR LEN(@configuration) > 100
        RAISERROR('Configuration must be a non-empty string with a maximum length of 100 characters.', 16, 1);

    UPDATE RamMemory
    SET configuration = @configuration
    WHERE ramId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateRAMFrequency
    @id INT,
    @frequency SMALLINT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @frequency IS NULL OR @frequency <= 0 OR @frequency > 10000
        RAISERROR('Frequency must be between 1 and 10,000 MHz.', 16, 1);

    UPDATE RamMemory
    SET frequency = @frequency
    WHERE ramId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateRAMLatency
    @id INT,
    @latency VARCHAR(100)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @latency IS NULL OR LEN(@latency) = 0 OR LEN(@latency) > 100
        RAISERROR('Latency must be a non-empty string with a maximum length of 100 characters.', 16, 1);

    UPDATE RamMemory
    SET latency = @latency
    WHERE ramId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateRAMPrice
    @id INT,
    @price SMALLINT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @price IS NULL OR @price <= 0 OR @price > 100000
        RAISERROR('Price must be between 1 and 100,000.', 16, 1);

    UPDATE RamMemory
    SET price = @price
    WHERE ramId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO
