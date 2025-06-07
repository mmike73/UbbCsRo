USE [PcPartsManager];
GO

EXEC createManufacturer @name='Bombitzu';
EXEC readManufacturer @id=35021;
EXEC updateManudacturerName @id=35021, @newName='Aorus'
EXEC deleteManufacturerById @id=35021;

EXEC createCPU
    @manufacturerId = 35007, 
    @model = 'Intel Core i7-13900KFC', 
    @baseClock = 3.0, 
    @boostClock = 5.8, 
    @socket = 'LGA1700', 
    @noCores = 24, 
    @noThreads = 32, 
    @fabricationTechnologyNM = 10, 
    @powerW = 125, 
    @price = 50;


EXEC readCPU @cpuId=23021;
EXEC updateCPUPrice @id=23021, @val=200;
EXEC deleteCPU @cpuId=23021;
--
EXEC readCPU @cpuId=23021;


EXEC createMotherboard
    @manufacturerId = 35012,
    @model = 'MSI B450 TOMAHAWK MAX MIHAIM',
    @boardFormat = 'ATX',
    @chipset = 'B450',
    @socket = 'AM4',
    @ramType = 'DDR4',
    @maximumMemorySize = 64,
    @pciEGeneration = 3.0,
    @integratedNetworkCard = 1,
    @bloetooth = 0,
    @price = 100;
EXEC readMotherboard @mbId=23003;
EXEC updateMotherboardMaximumMemSize @id=23003, @maximumMemorySize=1000;
EXEC deleteMotherboard @mbId=23003;
--
EXEC readMotherboard @mbId=23002;


EXEC createRAM
    @manufacturerId = 35014,
    @model = 'Kingston ValueRAM Ultra 50021',
    @type = 'DDR3',
    @stickFormat = 'DIMM',
    @sizeGb = 4,
    @configuration = 'Single Channel',
    @frequency = 1333,
    @latency = 'CL10',
    @price = 20;

EXEC readRAM @ramId=46;
EXEC updateRAMSizeGB @id=46, @sizeGb=100;
EXEC deleteRAM @ramId=46
--
EXEC readRAM @ramId=42;


EXEC createCPUMotherboard @cpuId=23022, @mbId=23008;
EXEC readCPUMotherboard @cpuId=23022, @mbId=23008;
EXEC deleteCPUMotherboard @cpuId=23022, @mbId=23008;

EXEC createMotherboardRamMemory @mbId=23008, @ramId=36;
EXEC readMotherboardRamMemory @mbId=23008, @ramId=36;
EXEC deleteMotherboardRamMemory @mbId=23008, @ramId=36;

SELECT * FROM vwCPURank
SELECT * FROM vwRAMRank


