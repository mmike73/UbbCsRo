USE [PcPartsManager];
GO

CREATE TABLE Logs (
    logId INT PRIMARY KEY IDENTITY(1, 1),
    actionDescription VARCHAR(255),
    timestamp DATETIME DEFAULT GETDATE(),
    isError BIT,
    errorMessage VARCHAR(255)
)

ALTER TABLE Motherboards
ADD CONSTRAINT UQ_Motherboards_Model UNIQUE (model);

CREATE PROCEDURE InsertCPUAndMotherboardWithTotalRollback
    @cpuManufacturerId INT,
    @cpuModel VARCHAR(100),
    @baseClock FLOAT,
    @boostClock FLOAT,
    @cpuSocket VARCHAR(100),
    @noCores SMALLINT,
    @noThreads SMALLINT,
    @fabricationTechnologyNM TINYINT,
    @powerW SMALLINT,
    @cpuPrice SMALLINT,

    @motherboardManufacturerId INT,
    @motherboardModel VARCHAR(51),
    @boardFormat VARCHAR(51),
    @chipset VARCHAR(50),
    @motherboardSocket VARCHAR(50),
    @ramType VARCHAR(10),
    @maximumMemorySize SMALLINT,
    @pciEGeneration FLOAT,
    @integratedNetworkCard BIT,
    @bloetooth BIT,
    @motherboardPrice SMALLINT
AS
BEGIN
    SET NOCOUNT ON;
    BEGIN TRY
        BEGIN TRANSACTION;
        EXEC dbo.createCPU
            @manufacturerId=@cpuManufacturerId,
            @model=@cpuModel,
            @baseClock=@baseClock,
            @boostClock=@boostClock,
            @socket=@cpuSocket,
            @noCores=@noCores,
            @noThreads=@noThreads,
            @fabricationTechnologyNM=@fabricationTechnologyNM,
            @powerW=@powerW,
            @price=@cpuPrice;

        INSERT INTO Logs (actionDescription, isError)
        VALUES ('CPU inserted: ' + @cpuModel, 0);

        EXEC dbo.createMotherboard
            @manufacturerId=@motherboardManufacturerId,
            @model=@motherboardModel,
            @boardFormat=@boardFormat,
            @chipset=@chipset,
            @socket=@motherboardSocket,
            @ramType=@ramType,
            @maximumMemorySize=@maximumMemorySize,
            @pciEGeneration=@pciEGeneration,
            @integratedNetworkCard=@integratedNetworkCard,
            @bloetooth=@bloetooth,
            @price=@motherboardPrice;

        -- add log for adding motherboard
        INSERT INTO Logs (actionDescription, isError)
        VALUES ('Motherboard inserted: ' + @motherboardModel, 0);


        DECLARE @newCpuId INT;
        SELECT @newCpuId = cpuId FROM CPUs WHERE
            manufacturerId=@cpuManufacturerId AND
            model=@cpuModel AND
            baseClock=@baseClock AND
            boostClock=@boostClock AND
            socket=@cpuSocket AND
            noCores=@noCores AND
            noThreads=@noThreads AND
            fabricationTehnologyNm=@fabricationTechnologyNM AND
            powerW=@powerW AND
            price=@cpuPrice;

        DECLARE @newMotherboardId INT;
        SELECT @newMotherboardId = motherboardId FROM Motherboards WHERE
            manufacturerId=@motherboardManufacturerId AND
            model=@motherboardModel AND
            boardFormat=@boardFormat AND
            chipset=@chipset AND
            socket=@motherboardSocket AND
            ramType=@ramType AND
            maximumMemorySize=@maximumMemorySize AND
            pciEGeneration=@pciEGeneration AND
            integratedNetworkCard=@integratedNetworkCard AND
            bloetooth=@bloetooth AND
            price=@motherboardPrice;

        EXEC dbo.createCPUMotherboard
            @cpuId=@newCpuId,
            @mbId=@newMotherboardId;

        -- log for added m-n relationship
        INSERT INTO Logs (actionDescription, isError)
        VALUES ('Created CPU-Motherboard link: CPU ' + CAST(@newCpuId AS VARCHAR) + ' <-> MB ' + CAST(@newMotherboardId AS VARCHAR), 0);

        COMMIT;
    END TRY
    BEGIN CATCH
        ROLLBACK;

        DECLARE @errors VARCHAR(255) = ERROR_MESSAGE();
        INSERT INTO Logs(actionDescription, isError, errorMessage)
        VALUES ('Error inserting CPU and Motherboard', 1, ERROR_MESSAGE());
        RAISERROR(@errors, 1, 1);

        THROW;
    END CATCH
END;

DROP PROCEDURE InsertCPUAndMotherboardWithTotalRollback;

EXEC InsertCPUAndMotherboardWithTotalRollback
    @cpuManufacturerId = 35008,
    @cpuModel = 'Ryzen 5 7600XXD',
    @baseClock = 4.7,
    @boostClock = 5.3,
    @cpuSocket = 'AM5',
    @noCores = 6,
    @noThreads = 12,
    @fabricationTechnologyNM = 5,
    @powerW = 105,
    @cpuPrice = 300,

    @motherboardManufacturerId = 35010,
    @motherboardModel = 'ASUS ROG STRIX B650E-F',
    @boardFormat = 'ATX',
    @chipset = 'B650E',
    @motherboardSocket = 'AM5',
    @ramType = 'DDR5',
    @maximumMemorySize = 128,
    @pciEGeneration = 5.0,
    @integratedNetworkCard = 1,
    @bloetooth = 1,
    @motherboardPrice = 250;


CREATE PROCEDURE InsertCPUAndMotherboard
    @cpuManufacturerId INT,
    @cpuModel VARCHAR(100),
    @baseClock FLOAT,
    @boostClock FLOAT,
    @cpuSocket VARCHAR(100),
    @noCores SMALLINT,
    @noThreads SMALLINT,
    @fabricationTechnologyNM TINYINT,
    @powerW SMALLINT,
    @cpuPrice SMALLINT,

    @motherboardManufacturerId INT,
    @motherboardModel VARCHAR(51),
    @boardFormat VARCHAR(51),
    @chipset VARCHAR(50),
    @motherboardSocket VARCHAR(50),
    @ramType VARCHAR(10),
    @maximumMemorySize SMALLINT,
    @pciEGeneration FLOAT,
    @integratedNetworkCard BIT,
    @bloetooth BIT,
    @motherboardPrice SMALLINT
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @cpuId INT = NULL;
    DECLARE @mbId INT = NULL;
    DECLARE @cpuSuccess BIT = 0;
    DECLARE @mbSuccess BIT = 0;

    BEGIN TRY

        SELECT @cpuId = cpuId FROM CPUs WHERE
            manufacturerId=@cpuManufacturerId AND
            model=@cpuModel AND
            baseClock=@baseClock AND
            boostClock=@boostClock AND
            socket=@cpuSocket AND
            noCores=@noCores AND
            noThreads=@noThreads AND
            fabricationTehnologyNm=@fabricationTechnologyNM AND
            powerW=@powerW AND
            price=@cpuPrice;

        IF @cpuId IS NULL
        BEGIN
            EXEC dbo.createCPU
                @manufacturerId=@cpuManufacturerId,
                @model=@cpuModel,
                @baseClock=@baseClock,
                @boostClock=@boostClock,
                @socket=@cpuSocket,
                @noCores=@noCores,
                @noThreads=@noThreads,
                @fabricationTechnologyNM=@fabricationTechnologyNM,
                @powerW=@powerW,
                @price=@cpuPrice;

            SELECT @cpuId = cpuId FROM CPUs WHERE
                manufacturerId=@cpuManufacturerId AND
                model=@cpuModel AND
                baseClock=@baseClock AND
                boostClock=@boostClock AND
                socket=@cpuSocket AND
                noCores=@noCores AND
                noThreads=@noThreads AND
                fabricationTehnologyNm=@fabricationTechnologyNM AND
                powerW=@powerW AND
                price=@cpuPrice;
        END;

        IF @cpuId = NULL
        BEGIN
            RAISERROR('CPU could not be inserted or found!', 1, 2);
        END;

        INSERT INTO Logs (actionDescription, isError)
        VALUES ('CPU inserted: ' + @cpuModel, 0);

    END TRY
    BEGIN CATCH

        INSERT INTO Logs(actionDescription, isError, errorMessage)
            VALUES ('Failed CPU insert', 1, ERROR_MESSAGE());

    END CATCH

    BEGIN TRY

        SELECT @mbId = motherboardId FROM Motherboards WHERE
            manufacturerId=@motherboardManufacturerId AND
            model=@motherboardModel AND
            boardFormat=@boardFormat AND
            chipset=@chipset AND
            socket=@motherboardSocket AND
            ramType=@ramType AND
            maximumMemorySize=@maximumMemorySize AND
            pciEGeneration=@pciEGeneration AND
            integratedNetworkCard=@integratedNetworkCard AND
            bloetooth=@bloetooth AND
            price=@motherboardPrice;

        IF @mbId IS NULL
        BEGIN
            EXEC dbo.createMotherboard
                @manufacturerId=@motherboardManufacturerId,
                @model=@motherboardModel,
                @boardFormat=@boardFormat,
                @chipset=@chipset,
                @socket=@motherboardSocket,
                @ramType=@ramType,
                @maximumMemorySize=@maximumMemorySize,
                @pciEGeneration=@pciEGeneration,
                @integratedNetworkCard=@integratedNetworkCard,
                @bloetooth=@bloetooth,
                @price=@motherboardPrice;

            SELECT @mbId = motherboardId FROM Motherboards WHERE
                manufacturerId=@motherboardManufacturerId AND
                model=@motherboardModel AND
                boardFormat=@boardFormat AND
                chipset=@chipset AND
                socket=@motherboardSocket AND
                ramType=@ramType AND
                maximumMemorySize=@maximumMemorySize AND
                pciEGeneration=@pciEGeneration AND
                integratedNetworkCard=@integratedNetworkCard AND
                bloetooth=@bloetooth AND
                price=@motherboardPrice;
        END;

        IF @mbId = NULL
        BEGIN
            RAISERROR('Motherboard could not be inserted or found!', 1, 2);
        END;

        INSERT INTO Logs (actionDescription, isError)
        VALUES ('Motherboard inserted: ' + @motherboardModel, 0);

    END TRY
    BEGIN CATCH

        INSERT INTO Logs(actionDescription, isError, errorMessage)
            VALUES ('Failed Motherboard insert', 1, ERROR_MESSAGE());

    END CATCH

    BEGIN TRY

        BEGIN TRANSACTION;
        EXEC dbo.createCPUMotherboard @cpuId, @mbId;
        INSERT INTO Logs(actionDescription, isError)
        VALUES ('Linked CPU ' + CAST(@cpuId AS VARCHAR) + ' with MB ' + CAST(@mbId AS VARCHAR), 0);
        COMMIT;

    END TRY
    BEGIN CATCH

        ROLLBACK;
        DECLARE @errors VARCHAR(255) = ERROR_MESSAGE();
        INSERT INTO Logs(actionDescription, isError, errorMessage)
        VALUES ('Failed M-N link', 1, ERROR_MESSAGE());
        RAISERROR(@errors, 1, 1);

    END CATCH

END;

DROP PROCEDURE InsertCPUAndMotherboard;


EXEC InsertCPUAndMotherboard
    @cpuManufacturerId = 35008,
    @cpuModel = '',
    @baseClock = 4.7,
    @boostClock = 5.3,
    @cpuSocket = 'AM5',
    @noCores = 6,
    @noThreads = 12,
    @fabricationTechnologyNM = 5,
    @powerW = 105,
    @cpuPrice = 300,

    @motherboardManufacturerId = 35010,
    @motherboardModel = 'ASUS ROG STRIX B650E-F',
    @boardFormat = 'ATX',
    @chipset = 'B650E',
    @motherboardSocket = 'AM5',
    @ramType = 'DDR5',
    @maximumMemorySize = 128,
    @pciEGeneration = 5.0,
    @integratedNetworkCard = 1,
    @bloetooth = 1,
    @motherboardPrice = 250;

EXEC InsertCPUAndMotherboard
    @cpuManufacturerId = 35008,
    @cpuModel = 'SomeCPU',
    @baseClock = 4.7,
    @boostClock = 5.3,
    @cpuSocket = 'AM5',
    @noCores = 6,
    @noThreads = 12,
    @fabricationTechnologyNM = 5,
    @powerW = 105,
    @cpuPrice = 300,

    @motherboardManufacturerId = 35010,
    @motherboardModel = '',
    @boardFormat = 'ATX',
    @chipset = 'B650E',
    @motherboardSocket = 'AM5',
    @ramType = 'DDR5',
    @maximumMemorySize = 128,
    @pciEGeneration = 5.0,
    @integratedNetworkCard = 1,
    @bloetooth = 1,
    @motherboardPrice = 250;