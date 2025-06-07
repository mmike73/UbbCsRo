USE [PcPartsManager];
GO

CREATE PROCEDURE updateMotherboardModel
    @id INT,
    @model VARCHAR(100)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @model IS NULL OR LEN(@model) = 0 OR LEN(@model) > 100
        RAISERROR('Model must be a non-empty string with a maximum length of 100 characters.', 16, 1);

    UPDATE Motherboards
    SET model = @model
    WHERE motherboardId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateMotherboardBoardFormat
    @id INT,
    @boardFormat VARCHAR(51)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @boardFormat IS NULL OR LEN(@boardFormat) = 0 OR LEN(@boardFormat) > 50
        RAISERROR('Board format must be a non-empty string with a maximum length of 50 characters.', 16, 1);

    UPDATE Motherboards
    SET boardFormat = @boardFormat
    WHERE motherboardId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateMotherboardChipset
    @id INT,
    @chipset VARCHAR(51)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @chipset IS NULL OR LEN(@chipset) = 0 OR LEN(@chipset) > 50
        RAISERROR('Chipset must be a non-empty string with a maximum length of 50 characters.', 16, 1);

    UPDATE Motherboards
    SET chipset = @chipset
    WHERE motherboardId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateMotherboardSocket
    @id INT,
    @socket VARCHAR(51)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @socket IS NULL OR LEN(@socket) = 0 OR LEN(@socket) > 50
        RAISERROR('Socket must be a non-empty string with a maximum length of 50 characters.', 16, 1);

    UPDATE Motherboards
    SET socket = @socket
    WHERE motherboardId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateMotherboardRamType
    @id INT,
    @ramType VARCHAR(11)
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @ramType IS NULL OR LEN(@ramType) = 0 OR LEN(@ramType) > 10
        RAISERROR('RAM type must be a non-empty string with a maximum length of 10 characters.', 16, 1);

    UPDATE Motherboards
    SET ramType = @ramType
    WHERE motherboardId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateMotherboardMaximumMemSize
    @id INT,
    @maximumMemorySize SMALLINT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @maximumMemorySize IS NULL OR @maximumMemorySize <= 0 OR @maximumMemorySize > 1024
        RAISERROR('Maximum memory size must be between 1 and 1024 GB.', 16, 1);

    UPDATE Motherboards
    SET maximumMemorySize = @maximumMemorySize
    WHERE motherboardId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateMotherboardPciEGeneration
    @id INT,
    @pciEGeneration FLOAT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @pciEGeneration IS NULL OR @pciEGeneration <= 0
        RAISERROR('PCIe generation must be a positive value.', 16, 1);

    UPDATE Motherboards
    SET pciEGeneration = @pciEGeneration
    WHERE motherboardId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateMotherboardIntegratedNetworkCard
    @id INT,
    @integratedNetworkCard BIT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    UPDATE Motherboards
    SET integratedNetworkCard = @integratedNetworkCard
    WHERE motherboardId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateMotherboardBluetooth
    @id INT,
    @bluetooth BIT
AS
BEGIN
    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    UPDATE Motherboards
    SET bloetooth = @bluetooth
    WHERE motherboardId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO

CREATE PROCEDURE updateMotherboardPrice
    @id INT,
    @price SMALLINT
AS
BEGIN

    IF @id IS NULL OR @id <= 0
        RAISERROR('ID must be a positive integer.', 16, 1);

    IF @price IS NULL OR @price <= 0 OR @price > 100000
        RAISERROR('Price must be between 1 and 100,000.', 16, 1);

    UPDATE Motherboards
    SET price = @price
    WHERE motherboardId = @id;

    IF @@ROWCOUNT = 0
        RAISERROR('No record found with the provided ID.', 16, 1);
END;
GO
