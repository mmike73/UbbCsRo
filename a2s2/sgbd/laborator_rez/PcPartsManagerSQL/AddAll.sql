USE [PcPartsManager];
GO

DELETE FROM Manufacturers
DELETE FROM CPUs
DELETE FROM Motherboards
DELETE FROM RamMemory
DELETE FROM CPUMotherboard
DELETE FROM MotherboardRamMemory

INSERT INTO Manufacturers (name) VALUES 
('Intel'), ('AMD'), ('NVIDIA'), ('Asus'), ('Gigabyte'), 
('MSI'), ('Corsair'), ('Kingston'), ('Samsung'), ('Seagate'),
('Western Digital'), ('ASRock'), ('Zotac'), ('PNY'), ('Palit'),
('Acer'), ('Lenovo'), ('Dell'), ('HP'), ('Toshiba');
GO

INSERT INTO CPUs (manufacturerId, model, baseClock, boostClock, socket, noCores, noThreads, fabricationTehnologyNm, powerW, price)
VALUES 
(35007, 'Intel Core i9-13900K', 3.0, 5.8, 'LGA1700', 24, 32, 10, 125, 600),
(35007, 'Intel Core i7-10700K', 3.8, 5.1, 'LGA1200', 8, 16, 14, 125, 400),
(35007, 'Intel Core i5-9600K', 3.7, 4.6, 'LGA1151', 6, 6, 14, 95, 250),
(35008, 'AMD Ryzen 9 5950X', 3.4, 4.9, 'AM4', 16, 32, 7, 105, 700),
(35008, 'AMD Ryzen 7 3700X', 3.6, 4.4, 'AM4', 8, 16, 7, 65, 300),
(35007, 'Intel Core i3-10100', 3.6, 4.3, 'LGA1200', 4, 8, 14, 65, 100),
(35008, 'AMD Athlon 3000G', 3.5, 3.5, 'AM4', 2, 4, 14, 35, 50),
(35008, 'AMD Ryzen 5 3600', 3.6, 4.2, 'AM4', 6, 12, 7, 65, 200),
(35007, 'Intel Pentium Gold G6400', 4.0, 4.0, 'LGA1200', 2, 4, 14, 58, 60),
(35007, 'Intel Core i5-12600K', 3.7, 4.9, 'LGA1700', 10, 16, 10, 125, 300),
(35007, 'Intel Core i7-12700F', 3.6, 5.0, 'LGA1700', 12, 20, 10, 125, 450),
(35008, 'AMD Ryzen 7 5800X', 3.8, 4.7, 'AM4', 8, 16, 7, 105, 450),
(35007, 'Intel Core i9-11900K', 3.5, 5.3, 'LGA1200', 8, 16, 10, 125, 500),
(35008, 'AMD Ryzen 9 3950X', 3.5, 4.7, 'AM4', 16, 32, 7, 105, 750),
(35008, 'AMD Ryzen 5 5600X', 3.7, 4.6, 'AM4', 6, 12, 7, 65, 300),
(35007, 'Intel Core i5-10400', 2.9, 4.3, 'LGA1200', 6, 12, 14, 65, 180);
GO

INSERT INTO RamMemory (manufacturerId, model, type, stickFormat, sizeGb, configuration, frequency, latency, price)
VALUES 
(35013, 'Corsair Vengeance LPX', 'DDR4', 'DIMM', 16, 'Dual Channel', 3200, 'CL16', 80),
(35014, 'Kingston HyperX Fury', 'DDR4', 'DIMM', 8, 'Single Channel', 2400, 'CL15', 40),
(35013, 'Corsair Dominator Platinum', 'DDR5', 'DIMM', 32, 'Quad Channel', 5200, 'CL40', 300),
(35015, 'Samsung EVO DDR4', 'DDR4', 'DIMM', 16, 'Dual Channel', 2666, 'CL18', 75),
(35014, 'Kingston Fury Renegade', 'DDR5', 'DIMM', 32, 'Dual Channel', 6000, 'CL36', 350),
(35013, 'Corsair ValueSelect', 'DDR3', 'DIMM', 8, 'Single Channel', 1600, 'CL11', 30),
(35014, 'Kingston ValueRAM', 'DDR3', 'DIMM', 4, 'Single Channel', 1333, 'CL10', 20),
(35013, 'Corsair Vengeance RGB Pro', 'DDR4', 'DIMM', 16, 'Dual Channel', 3600, 'CL18', 90),
(35014, 'Kingston Predator', 'DDR4', 'DIMM', 32, 'Quad Channel', 3200, 'CL16', 150),
(35015, 'Samsung DDR5 Module', 'DDR5', 'DIMM', 16, 'Dual Channel', 4800, 'CL40', 200),
(35013, 'Corsair Vengeance LPX2', 'DDR3', 'DIMM', 8, 'Single Channel', 1600, 'CL11', 35),
(35014, 'Kingston Fury Beast', 'DDR5', 'DIMM', 16, 'Dual Channel', 5600, 'CL40', 250),
(35013, 'Corsair Dominator DDR3', 'DDR3', 'DIMM', 8, 'Dual Channel', 1866, 'CL9', 45),
(35014, 'Kingston Fury Impact', 'DDR4', 'SODIMM', 16, 'Dual Channel', 3200, 'CL18', 95),
(35013, 'Corsair Vengeance SODIMM', 'DDR4', 'SODIMM', 16, 'Dual Channel', 2666, 'CL16', 85),
(35015, 'Samsung Laptop Memory', 'DDR3', 'SODIMM', 8, 'Single Channel', 1600, 'CL11', 40);
GO

INSERT INTO Motherboards (manufacturerId, model, boardFormat, chipset, socket, ramType, maximumMemorySize, pciEGeneration, integratedNetworkCard, bloetooth, price)
VALUES 
(35010, 'Asus ROG Strix Z690-E', 'ATX', 'Z690', 'LGA1700', 'DDR5', 128, 5.0, 1, 1, 400),
(35011, 'Gigabyte B550 Aorus Elite', 'ATX', 'B550', 'AM4', 'DDR4', 128, 4.0, 1, 0, 150),
(35011, 'Gigabyte A320M-S2H', 'Micro ATX', 'A320', 'AM4', 'DDR4', 64, 3.0, 1, 0, 70),
(35010, 'Asus TUF Gaming B560M-PLUS', 'Micro ATX', 'B560', 'LGA1200', 'DDR4', 128, 4.0, 1, 1, 200),
(35012, 'MSI MPG X570 GAMING PLUS', 'ATX', 'X570', 'AM4', 'DDR4', 128, 4.0, 1, 1, 180),
(35011, 'Gigabyte Z390 Aorus Ultra', 'ATX', 'Z390', 'LGA1151', 'DDR4', 128, 3.0, 1, 1, 250),
(35010, 'Asus Prime A320M-K', 'Micro ATX', 'A320', 'AM4', 'DDR4', 32, 3.0, 1, 0, 60),
(35010, 'Asus ROG Strix B450-F', 'ATX', 'B450', 'AM4', 'DDR4', 64, 3.0, 1, 1, 120),
(35011, 'Gigabyte Z690 Gaming X', 'ATX', 'Z690', 'LGA1700', 'DDR5', 128, 5.0, 1, 1, 350),
(35012, 'MSI B450 TOMAHAWK MAX', 'ATX', 'B450', 'AM4', 'DDR4', 64, 3.0, 1, 0, 100),
(35010, 'Asus ProArt B550-Creator', 'ATX', 'B550', 'AM4', 'DDR4', 128, 4.0, 1, 1, 230),
(35011, 'Gigabyte H510M S2H', 'Micro ATX', 'H510', 'LGA1200', 'DDR4', 64, 3.0, 1, 0, 90),
(35012, 'MSI MAG B660M', 'Micro ATX', 'B660', 'LGA1700', 'DDR4', 64, 4.0, 1, 1, 150),
(35010, 'Asus PRIME Z490-P', 'ATX', 'Z490', 'LGA1200', 'DDR4', 128, 4.0, 1, 1, 220),
(35011, 'Gigabyte A520M DS3H', 'Micro ATX', 'A520', 'AM4', 'DDR4', 64, 3.0, 1, 0, 70),
(35010, 'Asus ROG Maximus XIII Hero', 'ATX', 'Z590', 'LGA1200', 'DDR4', 128, 4.0, 1, 1, 380);
GO

INSERT INTO GPUs (manufacturerId, model, slot, vramType, sizeGb, baseClock, boostClock, memoryBus, powerW, price)
VALUES
(3, 'NVIDIA GeForce RTX 3090', 'PCIe 4.0', 'GDDR6X', 24, 1395, 1695, 384, 350, 1500),
(13, 'PNY GeForce GTX 1660 Super', 'PCIe 3.0', 'GDDR6', 6, 1530, 1785, 192, 125, 250),
(3, 'NVIDIA GeForce RTX 3080', 'PCIe 4.0', 'GDDR6X', 10, 1440, 1710, 320, 320, 800),
(14, 'Palit GeForce GT 1030', 'PCIe 3.0', 'GDDR5', 2, 1227, 1468, 64, 30, 80),
(3, 'NVIDIA GeForce RTX 3070 Ti', 'PCIe 4.0', 'GDDR6X', 8, 1575, 1770, 256, 290, 600),
(3, 'NVIDIA GeForce GTX 1050 Ti', 'PCIe 3.0', 'GDDR5', 4, 1290, 1392, 128, 75, 150),
(3, 'NVIDIA GeForce RTX 2060', 'PCIe 3.0', 'GDDR6', 6, 1365, 1680, 192, 160, 350),
(13, 'PNY GeForce RTX 3060', 'PCIe 4.0', 'GDDR6', 12, 1320, 1777, 192, 170, 500),
(3, 'NVIDIA GeForce GTX 1660', 'PCIe 3.0', 'GDDR5', 6, 1530, 1785, 192, 120, 200),
(3, 'NVIDIA Quadro RTX 4000', 'PCIe 3.0', 'GDDR6', 8, 1005, 1545, 256, 160, 900),
(13, 'PNY GeForce GT 710', 'PCIe 2.0', 'DDR3', 1, 954, 954, 64, 20, 40),
(14, 'Palit GeForce GTX 1650', 'PCIe 3.0', 'GDDR5', 4, 1485, 1665, 128, 75, 180),
(3, 'NVIDIA GeForce GTX 1080 Ti', 'PCIe 3.0', 'GDDR5X', 11, 1481, 1582, 352, 250, 500),
(3, 'NVIDIA GeForce RTX 3050', 'PCIe 4.0', 'GDDR6', 8, 1552, 1777, 128, 130, 300),
(13, 'PNY Quadro P620', 'PCIe 3.0', 'GDDR5', 2, 1265, 1265, 128, 40, 180);
GO

INSERT INTO ExternalMemory (manufacturerId, model, memoryCategory, interface, sizeTb, readSpeed, writeSpeed, price)
VALUES
(35015, 'Samsung 970 EVO Plus', 'SSD', 'M.2 NVMe', 1, 3500, 3300, 150),
(35016, 'Seagate Barracuda', 'HDD', 'SATA', 2, 220, 200, 60),
(35017, 'WD Blue', 'HDD', 'SATA', 4, 175, 150, 80),
(35015, 'Samsung 980 PRO', 'SSD', 'M.2 NVMe', 2, 7000, 5100, 300),
(35016, 'Seagate FireCuda', 'SSD', 'SATA', 1, 560, 540, 130),
(35017, 'WD Black SN850', 'SSD', 'M.2 NVMe', 1, 7000, 5300, 180),
(35015, 'Samsung T7', 'SSD', 'USB 3.2', 1, 1050, 1000, 120),
(35016, 'Seagate Backup Plus', 'HDD', 'USB 3.0', 5, 150, 140, 130),
(35017, 'WD My Passport', 'HDD', 'USB 3.0', 2, 120, 115, 60),
(35015, 'Samsung 860 EVO', 'SSD', 'SATA', 1, 550, 520, 100),
(35016, 'Seagate Exos X16', 'HDD', 'SATA', 16, 261, 249, 450),
(35017, 'WD Red NAS', 'HDD', 'SATA', 6, 180, 180, 140),
(35015, 'Samsung 870 QVO', 'SSD', 'SATA', 2, 560, 530, 150),
(35016, 'Seagate IronWolf', 'HDD', 'SATA', 4, 180, 180, 90),
(35017, 'WD Elements', 'HDD', 'USB 3.0', 3, 140, 130, 100);
GO

INSERT INTO Cases (manufacturerId, model, type, price)
VALUES
(35032, 'Cooler Master MasterBox Q300L', 'Micro ATX', 60),
(35033, 'NZXT H510', 'ATX Mid Tower', 70),
(35034, 'Fractal Design Meshify C', 'ATX Mid Tower', 90),
(35013, 'Corsair 4000D Airflow', 'ATX Mid Tower', 80),
(35035, 'Thermaltake View 71', 'ATX Full Tower', 150),
(35036, 'be quiet! Pure Base 500', 'ATX Mid Tower', 75),
(35037, 'Phanteks Eclipse P300A', 'ATX Mid Tower', 65),
(35038, 'Lian Li PC-O11 Dynamic', 'ATX Mid Tower', 140),
(35039, 'Deepcool Matrexx 55', 'ATX Mid Tower', 55),
(35032, 'Cooler Master HAF 912', 'ATX Mid Tower', 85),
(35013, 'Corsair Carbide Series 275R', 'ATX Mid Tower', 70),
(35040, 'SilverStone RL06', 'ATX Mid Tower', 95),
(35035, 'Thermaltake V200', 'ATX Mid Tower', 50),
(35041, 'Antec P120 Crystal', 'ATX Mid Tower', 100),
(35034, 'Fractal Design Define R6', 'ATX Mid Tower', 150),
(35032, 'Cooler Master MasterCase H500', 'ATX Mid Tower', 130),
(35013, 'Corsair iCUE 4000X RGB', 'ATX Mid Tower', 120),
(35038, 'Lian Li PC-011 Air', 'ATX Mid Tower', 140),
(35035, 'InWin 101', 'ATX Mid Tower', 80),
(35035, 'Thermaltake Versa H21', 'ATX Mid Tower', 40),
(35039, 'Deepcool Genome II', 'ATX Mid Tower', 180);
GO

INSERT INTO PowerSupplies (manufacturerId, model, powerW, certificate, price)
VALUES
(35013, 'Corsair RM750x', 750, '80+ Gold', 120),
(35014, 'Kingston KC600', 600, '80+ Bronze', 90),
(35013, 'Corsair CX550', 550, '80+ Bronze', 60),
(35014, 'Kingston KC650', 650, '80+ Bronze', 70),
(35013, 'Corsair AX1000', 1000, '80+ Titanium', 200),
(35014, 'Kingston KC500', 500, '80+ Bronze', 50),
(35013, 'Corsair VS450', 450, '80+ White', 40),
(35014, 'Kingston KC850', 850, '80+ Gold', 140),
(35013, 'Corsair HX1200', 1200, '80+ Platinum', 220),
(35013, 'Corsair CX750', 750, '80+ Bronze', 100),
(35014, 'Kingston KC300', 300, '80+ White', 30),
(35013, 'Corsair TX650M', 650, '80+ Gold', 85),
(35014, 'Kingston KC1000', 1000, '80+ Platinum', 180),
(35013, 'Corsair SF450', 450, '80+ Gold', 100),
(35014, 'Kingston KC750', 750, '80+ Silver', 110);
GO

INSERT INTO CPUMotherboard (cpuId, motherboardId) VALUES 
(1, 1), (1, 9), (1,13),
(10, 1), (10, 9), (10, 13),
(11, 1), (11, 9), (11, 13),
(2, 4), (2, 12), (2, 14), (2, 16), 
(6, 4), (6, 12), (6, 14), (6, 16), 
(9, 4), (9, 12), (9, 14), (9, 16),
(16, 4), (16, 12), (16, 14), (16, 16),
(3, 6), 
(4, 2), (4, 3), (4, 5), (4, 7), (4, 8), (4, 10), (4, 11), (4, 15), 
(5, 2), (5, 3), (5, 5), (5, 7), (5, 8), (5, 10), (5, 11), (5, 15), 
(7, 2), (7, 3), (7, 5), (7, 7), (7, 8), (7, 10), (7, 11), (7, 15), 
(8, 2), (8, 3), (8, 5), (8, 7), (8, 8), (8, 10), (8, 11), (8, 15), 
(12, 2), (12, 3), (12, 5), (12, 7), (12, 8), (12, 10), (12, 11), (12, 15), 
(14, 2), (14, 3), (14, 5), (14, 7), (14, 8), (14, 10), (14, 11), (14, 15), 
(15, 2), (15, 3), (15, 5), (15, 7), (15, 8), (15, 10), (15, 11), (15, 15);
GO

INSERT INTO MotherboardRamMemory (motherboardId, ramId) VALUES 
(2, 1), (2, 2), (2, 4), (2, 8), (2, 9), (2, 14), (2, 15), 
(3, 1), (3, 2), (3, 4), (3, 8), (3, 9), (3, 14), (3, 15), 
(4, 1), (4, 2), (4, 4), (4, 8), (4, 9), (4, 14), (4, 15), 
(5, 1), (5, 2), (5, 4), (5, 8), (5, 9), (5, 14), (5, 15), 
(6, 1), (6, 2), (6, 4), (6, 8), (6, 9), (6, 14), (6, 15), 
(7, 1), (7, 2), (7, 4), (7, 8), (7, 9), (7, 14), (7, 15), 
(8, 1), (8, 2), (8, 4), (8, 8), (8, 9), (8, 14), (8, 15), 
(9, 1), (9, 2), (9, 4), (9, 8), (9, 9), (9, 14), (9, 15), 
(10, 1), (10, 2), (10, 4), (10, 8), (10, 9), (10, 14), (10, 15),
(11, 1), (11, 2), (11, 4), (11, 8), (11, 9), (11, 14), (11, 15), 
(12, 1), (12, 2), (12, 4), (12, 8), (12, 9), (12, 14), (12, 15), 
(13, 1), (13, 2), (13, 4), (13, 8), (13, 9), (13, 14), (13, 15), 
(14, 1), (14, 2), (14, 4), (14, 8), (14, 9), (14, 14), (14, 15),
(15, 1), (15, 2), (15, 4), (15, 8), (15, 9), (15, 14), (15, 15), 
(16, 1), (16, 2), (16, 4), (16, 8), (16, 9), (16, 14), (16, 15),

(1, 3), (1, 5), (1, 10), (1, 12), 
(9, 3), (9, 5), (9, 10), (9, 12);
GO

INSERT INTO Builds (name, cpuId, motherboardId, ramId, memoryId, gpuId, powerSupplyId, caseId)
VALUES
('Budget Office Build', 23020, 23012, 29, 2, 4, 3, 2),
('Home Office Build', 23020, 23014, 33, 4, 12, 13, 2),

('Gaming Build',23018 , 23013, 30, 2, 13, 10, 8),

('Workstation Build', 23031, 23008, 30, 4, 2, 15, 18),
('High-Performance Workstation', 23018, 23009, 31, 2, 2, 9, 22),

('Budget Build', 23026, 23012, 29, 2, 4, 7, 2),
('Mid-range Build', 23032, 23004, 28, 4, 9, 15, 12),
('High-End Build', 23022, 23011, 30, 12, 15, 9, 9),

('Silent Build', 23032, 23004, 30, 4, 10, 4, 7),

('Overclocked Build', 23018, 23009, 30, 12, 2, 9, 16);
GO



-- prepwork

--HERE YOU CAN ADD A TABLE BY EXECUTING "EXEC insertIntoTables 'tableName'"
EXEC insertIntoTables 'Manufacturers';
EXEC insertIntoTables 'CPUs';
EXEC insertIntoTables 'CPUMotherboard';

SELECT * FROM Tables;

--HERE YOU CAN ADD A VIEW BY EXECUTING "EXEC insertIntoViews 'viewName'"
EXEC insertIntoViews 'vwManufacturers';
EXEC insertIntoViews 'vwCPUsManufacturers';
EXEC insertIntoViews 'vwCPUsMotherboards';

SELECT * FROM Views;


DECLARE @nrTables INT,@nrViews INT;
SELECT @nrTables = COUNT(*) FROM Tables;
SELECT @nrViews = COUNT(*) FROM Views;
EXEC insertIntoTests @nrTables,@nrViews;
GO
SELECT * FROM Tests;


--HERE YOU CAN INSERT THE MANNY TO MANNY RELATIONSIPS
EXEC insertIntoTestViews 1, 7;
EXEC insertIntoTestViews 2, 8;
EXEC insertIntoTestViews 7, 9;
SELECT * FROM TestViews;

--HERE YOU AN ADD TE MANNY TO MANNY RELATIONSIPS OR ADD A TEST WITH OTHER TEST CONFIGURATION
EXEC insertIntoTestTables 1,1,1000,1;
EXEC insertIntoTestTables 2,2,1000,1;
EXEC insertIntoTestTables 3,7,1000,1;
SELECT * FROM TestTables;

CREATE DATABASE [GestionareVanzari];
GO;

USE [GestionareVanzari];
GO;

CREATE TABLE Clienti (
    idClient INT PRIMARY KEY IDENTITY (1, 1),
    codFiscal INT UNIQUE,
    denumireClient VARCHAR(50)
);

CREATE TABLE Produse (
    idProdus INT PRIMARY KEY IDENTITY (1, 1),
    denumireProdus VARCHAR(50),
    unitateMasura VARCHAR(50)
);

CREATE TABLE AgentiVanzare (
    idAgent INT PRIMARY KEY identity (1, 1),
    nume VARCHAR(50),
    prenume VARCHAR(50)
);

CREATE TABLE Facturi (
    idFactura INT PRIMARY KEY IDENTITY (1, 1),
    dataEmitere DATETIME,
    idClient INT FOREIGN KEY REFERENCES CLienti(idClient),
    idAgent INT FOREIGN KEY REFERENCES AgentiVanzare(idAgent),
);

CREATE TABLE FacturaProdus (
    idFactura INT FOREIGN KEY REFERENCES Facturi(idFactura),
    idProdus INT FOREIGN KEY REFERENCES Produse(idProdus),
    numarOrdine INT,
    PRIMARY KEY (idFactura, idProdus, numarOrdine),
    cantitate INT,
    pret INT
);

CREATE PROCEDURE adaugaProdusFactura
    @idFactura INT,
    @idPRodus INT,
    @numarOrdine INT,
    @pret INT,
    @cantitate INT
AS
    BEGIN
        IF ((SELECT COUNT(*) FROM FacturaProdus WHERE idFactura = @idFactura AND idProdus = @idPRodus) = 0)
            INSERT INTO FacturaProdus(idFactura, idProdus, numarOrdine, cantitate, pret)
            VALUES (@idFactura, @idPRodus, @numarOrdine, @cantitate, @pret);
        ELSE
            INSERT INTO FacturaProdus(idFactura, idProdus, numarOrdine, cantitate, pret)
            VALUES (@idFactura, @idPRodus, @numarOrdine, -1, @pret);
    END;

EXEC adaugaProdusFactura @idFactura = 1, @idPRodus = 1, @numarOrdine = 2, @pret = 2000, @cantitate = 5;
EXEC adaugaProdusFactura @idFactura = 1, @idPRodus = 3, @numarOrdine = 3, @pret = 2000, @cantitate = 5;

CREATE VIEW facturiShaorma
AS
    SELECT
        F.idFactura AS IDFactura,
        F.dataEmitere AS DataEmitere,
        F.idClient AS IDClient,
        F.idAgent AS idAgent
    FROM Facturi F
        INNER JOIN FacturaProdus FP ON F.idFactura = FP.idFactura
        INNER JOIN Produse P ON FP.idProdus = P.idProdus
        WHERE  P.denumireProdus = 'Shaorma' AND FP.pret = 25

DROP VIEW facturiShaorma;

SELECT * FROM facturiShaorma;


CREATE FUNCTION statsFacturi()
    RETURNS @statsFacturi TABLE (Luna INT, NumeAgent VARCHAR(50), PrenumeAgent VARCHAR(50), ValoareaTotala INT)
AS
    BEGIN
        INSERT INTO @statsFacturi (Luna, NumeAgent, PrenumeAgent, ValoareaTotala)
        SELECT
            MONTH(F.dataEmitere) AS Luna,
            A.nume AS NumeAgent,
            A.prenume AS PrenumeAgent,
            SUM(FP.cantitate * FP.pret) AS ValoareaTotala
        FROM Facturi F
            INNER JOIN FacturaProdus FP ON F.idFactura = FP.idFactura
            INNER JOIN AgentiVanzare A ON F.idAgent = A.idAgent
        GROUP BY MONTH(F.dataEmitere), A.prenume, A.nume
        ORDER BY MONTH(F.dataEmitere), A.nume;
        RETURN;
    END;

DROP FUNCTION statsFacturi;

SELECT * FROM dbo.statsFacturi();


INSERT INTO Clienti (codFiscal, denumireClient) VALUES
(123456789, 'SC Exemplu SRL'),
(987654321, 'SC Alta Firma SRL'),
(456123789, 'SC Teste SRL');

INSERT INTO Produse (denumireProdus, unitateMasura) VALUES
('Laptop', 'bucata'),
('Shaorma', 'bucata'),
('Telefon', 'bucata'),
('Televizor', 'bucata');

INSERT INTO AgentiVanzare (nume, prenume) VALUES
('Popescu', 'Ion'),
('Ionescu', 'Maria'),
('Georgescu', 'Andrei');

INSERT INTO Facturi (dataEmitere, idClient, idAgent) VALUES
('2025-02-01', 1, 1),
('2025-02-15', 2, 2),
('2025-02-18', 3, 1);

INSERT INTO FacturaProdus (idFactura, idProdus, numarOrdine, cantitate, pret) VALUES
(1, 1, 1, 2, 3000), -- Laptop x 2 la 3000 lei fiecare
(1, 2, 2, 5, 25),   -- Shaorma x 5 la 25 lei fiecare
(2, 3, 1, 1, 2500), -- Telefon x 1 la 2500 lei
(2, 4, 2, 1, 4000), -- Televizor x 1 la 4000 lei
(3, 2, 1, 10, 30);  -- Shaorma x 10 la 30 lei fiecare


CREATE DATABASE NoteFilme;
GO

USE NoteFilme;
GO

CREATE TABLE Utilizatori (
    utilizatorId INT PRIMARY KEY IDENTITY (1, 1),
    numeUtilizator VARCHAR(50) UNIQUE NOT NULL,
    parola VARCHAR(50),
    adresaEmail VARCHAR(50) UNIQUE,
);
GO

CREATE TABLE Companii (
    companieId INT PRIMARY KEY IDENTITY(1, 1),
    nume VARCHAR(50)-- UNIQUE,
    tara VARCHAR(50),
    CONSTRAINT uq_nume UNIQUE (nume)
);
GO

CREATE TABLE Filme (
    filmId INT PRIMARY KEY IDENTITY(1, 1),
    companieId INT,
    titlu VARCHAR(50) UNIQUE,
    durata INT,
    limba VARCHAR(50),
    CONSTRAINT fk_CompaniiFilme FOREIGN KEY (companieId) references Companii(companieId) ON UPDATE CASCADE ON DELETE CASCADE,
);
GO

CREATE TABLE Note (
    utilizatorId INT,
    filmId INT,
    nota INT,
    CONSTRAINT fk_UtilizatoriNote FOREIGN KEY (utilizatorId) REFERENCES Utilizatori(utilizatorId),
    CONSTRAINT fk_FilmeNote FOREIGN KEY (filmId) REFERENCES Filme(filmId),
    CONSTRAINT pk_Note PRIMARY KEY (utilizatorId, filmId),
    CONSTRAINT ck_Nota CHECK (nota >= 1 AND nota <= 10)
);
GO
-- varianta cu alter table
-- ALTER TABLE Note ADD CONSTRAINT ck_Nota CHECK (nota >= 1 AND nota <= 10);

ALTER TABLE Utilizatori
ADD CONSTRAINT uq_email UNIQUE (email);

-- adauga un ckeck pentru mai multe coloane
ALTER TABLE Note
ADD CONSTRAINT ck_nota CHECK (nota>=1 AND nota <= 10);

ALTER TABLE Note
ADD data_si_ora_adaugarii DATETIME;

ALTER TABLE Note
ADD CONSTRAINT df_data_si_ora_adaugarii DEFAULT GETDATE() FOR data_si_ora_adaugarii;

ALTER TABLE Filme
ALTER COLUMN titlu VARCHAR(220);

ALTER TABLE Note
DROP CONSTRAINT df_data_si_ora_adaugarii;

ALTER TABLE Note
DROP COLUMN data_si_ora_adaugarii;

ALTER DATABASE NoteFilme
MODIFY Name=ProblemaFilme;

CREATE DATABASE [ParcDistractii];
GO

USE [ParcDistractii];
GO

CREATE TABLE CategoriiVizitatori (
    categorieVizitatoriId INT PRIMARY KEY IDENTITY (1, 1),
    numeCategorie VARCHAR(50),
);
GO

CREATE TABLE Vizitatori (
    vizitatorId INT PRIMARY KEY IDENTITY (1, 1),
    categorieVizitatoriId INT FOREIGN KEY REFERENCES CategoriiVizitatori,
    nume VARCHAR(50) UNIQUE,
    email VARCHAR(50) UNIQUE,
);
GO

CREATE TABLE Sectiuni (
    sectiuneId INT PRIMARY KEY IDENTITY (1, 1),
    numeSectiune VARCHAR(50) UNIQUE,
    descriereSectiune VARCHAR(200)
);
GO

CREATE TABLE Atractii (
    atractieId INT PRIMARY KEY IDENTITY (1, 1),
    sectiuneId INT FOREIGN KEY REFERENCES Sectiuni(sectiuneId),
    numeAtractie VARCHAR(50) UNIQUE,
    descriereAtractie VARCHAR(200),
    varstaMinima INT
);
GO

CREATE TABLE NotaAtractie (
    vizitatorId INT,
    atractieId INT,
    nota INT,
    CONSTRAINT fk_VizitatorNota FOREIGN KEY (vizitatorId) REFERENCES Vizitatori(vizitatorId) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_AtractieNota FOREIGN KEY (atractieId) REFERENCES Atractii(atractieId) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT pk_NotaAtractie PRIMARY KEY (vizitatorId, atractieId)
);
GO

INSERT INTO CategoriiVizitatori (numeCategorie)
VALUES
('Copii'),
('Adulți'),
('Seniori'),
('Grupuri');

INSERT INTO Vizitatori (categorieVizitatoriId, nume, email)
VALUES
(1, 'Andrei Popescu', 'andrei.popescu@email.com'),
(2, 'Maria Ionescu', 'maria.ionescu@email.com'),
(3, 'Ion Gheorghe', 'ion.gheorghe@email.com'),
(4, 'Grup Școala 123', 'contact@scoala123.com');

INSERT INTO Vizitatori (categorieVizitatoriId, nume)
VALUES
(3, 'Todor Gheorghe');

INSERT INTO Sectiuni (numeSectiune, descriereSectiune)
VALUES
('Zona Acvatică', 'Include piscine și tobogane acvatice.'),
('Adrenalină', 'Zona pentru atracții extreme și senzații tari.'),
('Copii', 'Atracții dedicate copiilor sub 12 ani.'),
('Relaxare', 'Zone pentru odihnă și activități relaxante.');
INSERT INTO Sectiuni (numeSectiune, descriereSectiune)
VALUES
('Celaxare', 'Zone pentru odihnă și activități relaxante.');
('Relaxare', 'Zone pentru odihnă și activități relaxante.');
INSERT INTO Sectiuni (numeSectiune, descriereSectiune)
VALUES
('Nene', 'Zone pentru odihnă și activități relaxante.'),
('Baaaaanun', 'Zone pentru odihnă și activități relaxante.'),
('n', 'Zone pentru odihnă și activități relaxante.'),
('Nen', 'Zone pentru odihnă și activități relaxante.');


INSERT INTO Atractii (numeAtractie, descriereAtractie, varstaMinima)
VALUES
('Piscina cu Valuri', 'Piscină simulând valuri oceanice.', 8),
( 'Roller Coaster', 'Montagne russe cu viteză mare.', 14),
( 'Carusel', 'Carusel clasic pentru copii.', 3),
('Cinema 7D', 'Experiență de cinema interactivă.', 12);

INSERT INTO NotaAtractie (vizitatorId, atractieId, nota)
VALUES
(1, 4, 9),
(2, 2, 8),
(3, 3, 10),
(4, 4, 7),
(3, 4, 6);


DROP TABLE Atractii;
DROP TABLE Sectiuni;
DROP TABLE Vizitatori;
DROP TABLE CategoriiVizitatori;
DROP TABLE NotaAtractie;

INSERT INTO Sectiuni (numeSectiune, descriereSectiune) VALUES
                                                           ('Sectiunea 1', 'cea mai mare');

INSERT INTO Atractii (sectiuneId, numeAtractie, descriereAtractie, varstaMinima) VALUES
                                                                                     (2,  'rollercoaster mic', 'al mai mic', 6);

UPDATE Sectiuni SET descriereSectiune='cea mai veche'
WHERE numeSectiune='Sectiunea 1';

DELETE FROM Atractii WHERE numeAtractie = 'rollercoaster';

DELETE FROM Sectiuni WHERE numeSectiune = 'Sectiunea 1';

SELECT sectiuneId, numeSectiune, descriereSectiune FROM Sectiuni;

SELECT DISTINCT varstaMinima FROM Atractii;

SELECT numeAtractie, descriereAtractie FROM Atractii where varstaMinima = 12;

SELECT numeAtractie, descriereAtractie FROM Atractii where numeAtractie <> 'lista neagra';

SELECT * FROM Atractii WHERE varstaMinima > 11 AND varstaMinima < 16;
SELECT * FROM Atractii WHERE varstaMinima BETWEEN 11 AND 16;
SELECT * FROM Atractii WHERE varstaMinima NOT BETWEEN 11 AND 16;
SELECT * FROM Atractii WHERE varstaMinima IN (12, 14, 15, 16);
SELECT * FROM Atractii WHERE varstaMinima NOT IN (12, 14, 15, 16);

SELECT * FROM Vizitatori WHERE nume LIKE 'A%'; -- incepe cu A
SELECT * FROM Vizitatori WHERE nume LIKE '%a'; -- se termina cu a
SELECT * FROM Vizitatori WHERE nume LIKE '%ana%'; -- contine ana
SELECT * FROM Vizitatori WHERE nume LIKE '_na'; -- are 3 litere si se termina cu na Dna Ana pna
SELECT * FROM Vizitatori WHERE nume LIKE '[ABC]%'; -- incepe cu a, b sau c
SELECT * FROM Vizitatori WHERE nume LIKE '[^ABC]%'; -- nu incepe cu a,b sau c

SELECT * FROM Vizitatori WHERE email IS NULL;
SELECT * FROM Vizitatori WHERE email IS NOT NULL;

SELECT C.numeCategorie AS categorie, V.nume, V.email FROM CategoriiVizitatori C, Vizitatori V
WHERE C.categorieVizitatoriId = V.vizitatorId;

-- folosind inner join
SELECT C.numeCategorie AS categorie, V.nume, V.email FROM CategoriiVizitatori C
INNER JOIN Vizitatori V ON C.categorieVizitatoriId = V.vizitatorId;

-- nu au ptimit nota 9, dar au ptimit o nota
SELECT numeAtractie FROM AtractiiD
                    WHERE atractieId <> ALL (SELECT atractieId FROM NotaAtractie WHERE nota = 9) -- equiv NOT IN
                    AND atractieId IN (SELECT atractieId FROM NotaAtractie);

-- NU AU PRIMIT NICIODATA NOTA 9, DAR AU PRIMIT CEL PUTIN O DATA NOTA 10
SELECT numeAtractie FROM Atractii
WHERE atractieId IN (SELECT atractieId FROM NotaAtractie WHERE nota=10)
EXCEPT -- \ MINUS IN MULTIMI
SELECT numeAtractie FROM Atractii
WHERE atractieId IN (SELECT atractieId FROM NotaAtractie WHERE nota=9);

-- cel putin odata nota 9 sau cel putin o data nota 10
SELECT numeAtractie FROM Atractii
WHERE atractieId IN (SELECT atractieId FROM NotaAtractie WHERE nota=10)
UNION -- SAU UNION ALL - pentru a include duplicate \ REUNIUNE IN MULTIMI
SELECT numeAtractie FROM Atractii
WHERE atractieId IN (SELECT atractieId FROM NotaAtractie WHERE nota=9);

-- care au note de 9 și de 10
SELECT numeAtractie FROM Atractii
WHERE atractieId IN (SELECT atractieId FROM NotaAtractie WHERE nota=10)
INTERSECT -- INTERSECTIE IN MULTIMI
SELECT numeAtractie FROM Atractii
WHERE atractieId IN (SELECT atractieId FROM NotaAtractie WHERE nota=9);

-- PENSIIONARI / COPIII
SELECT * FROM CategoriiVizitatori WHERE numeCategorie IN ('pensionari', 'copii');

-- sectiuni care incep cu C
SELECT * FROM Sectiuni WHERE numeSectiune LIKE 'C%';

-- SE TERMINA CU LITERA N SI AU CEL PUTIN 2 CARACTERE
SELECT * FROM Sectiuni WHERE numeSectiune LIKE '%_n';

-- VIZITATORII CARE NU AU DAT NOTE
SELECT nume FROM Vizitatori WHERE vizitatorId <> ALL (SELECT vizitatorId FROM NotaAtractie);

-- numele vizitatoriloe + numaruld enote acordate
SELECT
    V.nume AS numeViz,
    N.nota AS nota,
    A.numeAtractie AS numeA
FROM
    Vizitatori V
    INNER JOIN NotaAtractie N ON V.vizitatorId = N.vizitatorId
    INNER JOIN Atractii A ON A.atractieId = N.atractieId;

-- numele vizitatoriloe + numaruld enote acordate
SELECT
    V.nume AS numeViz,
    N.nota AS nota,
    A.numeAtractie AS numeA
FROM
    Vizitatori V
    LEFT OUTER JOIN NotaAtractie N ON V.vizitatorId = N.vizitatorId
    LEFT OUTER JOIN Atractii A ON A.atractieId = N.atractieId;

-- toate notele acordate
SELECT DISTINCT nota FROM NotaAtractie;

-- nume sectiune, descriere atractii pentru toate sectiunile care au cel putin o atractie asociata
SELECT
    S.numeSectiune AS NumeSectiune,
    A.numeAtractie AS NumeAtractie,
    A.descriereAtractie AS DescriereAtractie
FROM
    Sectiuni S INNER JOIN Atractii A ON S.sectiuneId = A.sectiuneId;

-- numele, varsta minima  pentru atr care au cel putin 2 note
SELECT
    A.numeAtractie AS Nume,
    A.varstaMinima AS VarstaMinima
FROM
    Atractii A WHERE 2 <= (SELECT COUNT(N.nota) AS NrNote FROM NotaAtractie N WHERE A.atractieId = N.atractieId);

-- categotie + nume vizitator + nota + atractia + descrierea
-- pentru non-adulti
SELECT
    C.numeCategorie AS Categorie,
    V.nume AS NumeVizitator,
    N.nota AS Nota,
    A.numeAtractie AS Atractie,
    A.descriereAtractie AS Descriere
FROM
    CategoriiVizitatori C
    INNER JOIN Vizitatori V ON V.categorieVizitatoriId = C.categorieVizitatoriId
    INNER JOIN NotaAtractie N ON N.vizitatorId = V.vizitatorId
    INNER JOIN Atractii A ON A.atractieId = N.atractieId
WHERE C.numeCategorie <> 'adult';

-- nota maxima
SELECT
    A.numeAtractie AS Atractie,
    MAX(N.nota) AS NotaMax
FROM
    Atractii A
    INNER JOIN NotaAtractie N ON A.atractieId = N.atractieId
GROUP BY
    A.numeAtractie;

-- nota minima
SELECT
    A.numeAtractie AS Atractie,
    MIN(N.nota) AS NotaMax
FROM
    Atractii A
    INNER JOIN NotaAtractie N ON A.atractieId = N.atractieId
GROUP BY
    A.numeAtractie;

-- proceduri stocate

CREATE PROCEDURE AdaugaConstrangereDefaultVarsta
AS
BEGIN
    ALTER TABLE Atractii
    ADD CONSTRAINT df_varstaMinima DEFAULT 12 FOR varstaMinima;
END;

EXEC AdaugaConstrangereDefaultVarsta;

-- nume, descriere, varsta min pentru un param

CREATE PROCEDURE ReturneazaAtractiiCuVarstaMin
    @varstaMin INT
AS
    BEGIN
        SELECT numeAtractie, descriereAtractie, varstaMinima FROM Atractii
        WHERE varstaMinima=@varstaMin;
    END;

EXEC ReturneazaAtractiiCuVarstaMin 12;
EXEC ReturneazaAtractiiCuVarstaMin @varstaMin = 12;

-- MODIFICA - RETURNEASZA NUMARUL DE ATRACTII DE ACEST FEL
ALTER PROCEDURE ReturneazaAtractiiCuVarstaMin
    @varstaMin INT,
    @nrAtractii INT OUTPUT
AS
    BEGIN
        SELECT @nrAtractii = COUNT(*) FROM Atractii WHERE varstaMinima = @varstaMin;
    END;

DECLARE @nrAtractii AS INT;
SET @nrAtractii=0;
EXEC ReturneazaAtractiiCuVarstaMin @varstaMin = 12, @nrAtractii=@nrAtractii OUTPUT;
PRINT @nrAtractii;

-- generare mesaje eroare

ALTER PROCEDURE ReturneazaAtractiiCuVarstaMin
    @varstaMin INT,
    @nrAtractii INT OUTPUT
AS
    BEGIN
        SELECT @nrAtractii = COUNT(*) FROM Atractii WHERE varstaMinima=@varstaMin;
        IF (@nrAtractii=0)
            RAISERROR('Nu a fost returnată nicio atracție!', 16, 1);-- message, severity, state
    END;


CREATE PROCEDURE VerificaVarstaMin
    @atractieId INT
AS
    BEGIN
        IF ((SELECT varstaMinima FROM Atractii WHERE atractieId=@atractieId) = 12)
            RETURN 1;
        ELSE
            RETURN 2;
    END;

DECLARE @status INT;
EXEC @status = VerificaVarstaMin 5;
SELECT 'Status'=@status;
GO

-- introduce sectiune noua
CREATE PROCEDURE InsereazaSectiuneNoua
    @numeSectiuneNoua VARCHAR(50),
    @descriereSectiuneNoua VARCHAR(50)
AS
    BEGIN
        INSERT INTO Sectiuni (numeSectiune, descriereSectiune)
        VALUES (@numeSectiuneNoua, @descriereSectiuneNoua);
    END;

EXEC InsereazaSectiuneNoua @numeSectiuneNoua = 'Padurea Spanzuratilor', @descriereSectiuneNoua = 'Horror Strigoi una alta';
SELECT * FROM Sectiuni;

-- instroduce categorie noua
CREATE PROCEDURE InsereazaCategorieNoua
    @numeCategorieNoua VARCHAR(50)
AS
    BEGIN
        IF ((SELECT COUNT(*) FROM CategoriiVizitatori WHERE numeCategorie=@numeCategorieNoua) > 0)
            RAISERROR('CATEGORIA DEJA EXISTA!!!',16,1);
        ELSE
            INSERT INTO CategoriiVizitatori(numeCategorie)
            VALUES (@numeCategorieNoua);
    END;
    
EXEC InsereazaCategorieNoua @numeCategorieNoua = 'Grupuri';

--exercitiul 3

CREATE PROCEDURE IsereazaAtractieNoua
    @numeAtractieNoua VARCHAR(50),
    @descriereAtractieNoua VARCHAR(200),
    @varstaMinimaAtractieNoua INT,
    @numeSectiune VARCHAR(50)
AS
    BEGIN
        DECLARE @sectiuneId INT;
        SET @sectiuneId = (SELECT sectiuneId FROM Sectiuni WHERE numeSectiune=@numeSectiune);
        IF (@sectiuneId IS NULL)
        BEGIN
            INSERT INTO Sectiuni (numeSectiune) VALUES (@numeSectiune);
            SET @sectiuneId = (SELECT sectiuneId FROM Sectiuni WHERE numeSectiune=@numeSectiune);
        END;

        INSERT INTO Atractii (sectiuneId, numeAtractie, descriereAtractie, varstaMinima)
        VALUES (@sectiuneId,@numeAtractieNoua, @descriereAtractieNoua, @varstaMinimaAtractieNoua);
    END;

EXEC IsereazaAtractieNoua @numeAtractieNoua = 'Germania', @descriereAtractieNoua = 'Uber allen', @varstaMinimaAtractieNoua = 5, @numeSectiune = 'Europa';
EXEC IsereazaAtractieNoua @numeAtractieNoua = 'Austria', @descriereAtractieNoua = 'Uber allen', @varstaMinimaAtractieNoua = 5, @numeSectiune = 'Europa';
SELECT * FROM Sectiuni;
SELECT * FROM Atractii;

-- exista user cu adresa de mail

CREATE PROCEDURE ExistaVizitatorCuEmail
    @email VARCHAR(50),
    @vizitatorId INT OUTPUT
AS
    BEGIN
        SET NOCOUNT ON;
        SELECT @vizitatorId = vizitatorId FROM Vizitatori WHERE email = @email;

        IF @vizitatorId IS NULL
            RAISERROR('NU EXITA VIZITATORI CU ACEST EMAIL', 16,1);
    END;

DECLARE @vizitatorId INT;
EXEC ExistaVizitatorCuEmail @email = 'ion.gheorghe@email.com', @vizitatorId=@vizitatorId OUTPUT;
SELECT @vizitatorId;

-- insereaza o notă în tabelul note
CREATE PROCEDURE InsereazaNota
    @atractieIdNou INT,
    @vizitatorId INT,
    @nota INT
AS
    BEGIN
        IF ((SELECT COUNT(*) FROM Atractii WHERE atractieId = @atractieIdNou) = 0)
            RAISERROR('NU EXISTA ATRACTIE CU ID-UL INTRODUS',16,1);
        IF ((SELECT COUNT(*) FROM Atractii WHERE atractieId = @atractieIdNou) = 0)
            RAISERROR('NU EXISTA ATRACTIE CU ID-UL INTRODUS',16,2);
        INSERT INTO NotaAtractie (vizitatorId, atractieId, nota)
        VALUES (@vizitatorId, @atractieIdNou, @nota);
    END;

EXEC InsereazaNota @atractieIdNou = 2, @vizitatorId = 2, @nota = 10;

-- actualizeaza adresa de email a unui vizitator din tabelul vizitatori
CREATE PROCEDURE ActualizeazaAdresaMail
    @vizitatorId INT,
    @emailNou VARCHAR(50)
AS
    BEGIN
        IF ((SELECT COUNT(*) FROM Vizitatori WHERE vizitatorId = @vizitatorId) = 0)
            RAISERROR('VIZITATORUL CU ID DAT NU EXISTA',16,1);
        UPDATE Vizitatori SET email = @emailNou where vizitatorId = @vizitatorId;
    END;

EXEC ActualizeazaAdresaMail @vizitatorId = 2, @emailNou = 'vericu@vericel.com';

-- returneaza numele vizitatorului, adresa de email si numarul total de note
-- pentru toti care au cel putin o nota

CREATE PROCEDURE NumarNoteVizitatori
AS
    BEGIN
        SELECT
            V.nume AS NumeVizitator,
            V.email AS EmailVizitator,
            COUNT(N.nota) AS NrNote
        FROM
            Vizitatori V
            INNER JOIN NotaAtractie N ON V.vizitatorId = N.vizitatorId
        GROUP BY V.nume, V.email;
    END;

EXEC NumarNoteVizitatori;

CREATE FUNCTION EcistaCategorie(@nume VARCHAR(70))
    RETURNS VARCHAR(20) 
AS
    BEGIN
        IF (EXISTS (SELECT * FROM Categorii WHERE nume=@nume))
            RETURN 'EXISTA'
        RETURN 'NU EXISTA'
    END;

CREATE FUNCTION ReturneazaNoteAtractii(@varsatMin INT)
    RETURNS TABLE 
AS
    RETURN SELECT
        A.nume,
        N.nota,
        V.email
    FROM
        Atractii a
        INNER JOIN Note N ON A.idAtractie = N.idAtractie
        INNER JOIN Vizitatori V ON N.idVizitator = V.idVizitator
    WHERE
        A.varsatMin=@varstaMin;
    
SELECT * FROM dbo.ReturneazaNoteAtractii(12);


CREATE FUNCTION NoteAtractii(@email VARCHAR(100))
    RETURNS @NoteAtractii TABLE (atractie VARCHAR(100), email VARCHAR(100), nota REAL, tip_evaluare VARCHAR(10))
AS
    BEGIN
        INSERT INTO @NoteAtractii (atractie, nota, email)
        SELECT 
            A.nume,
            N.nota, 
            V.email 
        FROM
            Atractii A
            INNER JOIN Note N ON A.idAtractie = N.idAtractie
        WHERE
            V.EMAIL = @email
        UPDATE @NoteAtractii SET tip_evaluare='pozitiva' WHERE nota>=5.0;
        UPDATE @NoteAtractii SET tip_evaluare='negativa' WHERE nota<5.0;
    END;

SELECT * FROM dbo.NoteAtractii('mihaimoldovan@gmail.com');


-- sterge o atractie din tabelul atractii dupa numele atractieiu
-- daca exista note date - mesaj si nu se va sterge

CREATE DATABASE [GestionareVanzari];
GO;

USE [GestionareVanzari];
GO;

CREATE TABLE Clienti (
    idClient INT PRIMARY KEY IDENTITY (1, 1),
    codFiscal INT UNIQUE,
    denumireClient VARCHAR(50)
);

CREATE TABLE Produse (
    idProdus INT PRIMARY KEY IDENTITY (1, 1),
    denumireProdus VARCHAR(50),
    unitateMasura VARCHAR(50)
);

CREATE TABLE AgentiVanzare (
    idAgent INT PRIMARY KEY identity (1, 1),
    nume VARCHAR(50),
    prenume VARCHAR(50)
);

CREATE TABLE Facturi (
    idFactura INT PRIMARY KEY IDENTITY (1, 1),
    dataEmitere DATETIME,
    idClient INT FOREIGN KEY REFERENCES CLienti(idClient),
    idAgent INT FOREIGN KEY REFERENCES AgentiVanzare(idAgent),
);

CREATE TABLE FacturaProdus (
    idFactura INT FOREIGN KEY REFERENCES Facturi(idFactura),
    idProdus INT FOREIGN KEY REFERENCES Produse(idProdus),
    numarOrdine INT,
    PRIMARY KEY (idFactura, idProdus, numarOrdine),
    cantitate INT,
    pret INT
);

CREATE PROCEDURE adaugaProdusFactura
    @idFactura INT,
    @idPRodus INT,
    @numarOrdine INT,
    @pret INT,
    @cantitate INT
AS
    BEGIN
        IF ((SELECT COUNT(*) FROM FacturaProdus WHERE idFactura = @idFactura AND idProdus = @idPRodus) = 0)
            INSERT INTO FacturaProdus(idFactura, idProdus, numarOrdine, cantitate, pret)
            VALUES (@idFactura, @idPRodus, @numarOrdine, @cantitate, @pret);
        ELSE
            INSERT INTO FacturaProdus(idFactura, idProdus, numarOrdine, cantitate, pret)
            VALUES (@idFactura, @idPRodus, @numarOrdine, -1, @pret);
    END;

EXEC adaugaProdusFactura @idFactura = 1, @idPRodus = 1, @numarOrdine = 2, @pret = 2000, @cantitate = 5;
EXEC adaugaProdusFactura @idFactura = 1, @idPRodus = 3, @numarOrdine = 3, @pret = 2000, @cantitate = 5;

CREATE VIEW facturiShaorma
AS
    SELECT
        F.idFactura AS IDFactura,
        F.dataEmitere AS DataEmitere,
        F.idClient AS IDClient,
        F.idAgent AS idAgent
    FROM Facturi F
        INNER JOIN FacturaProdus FP ON F.idFactura = FP.idFactura
        INNER JOIN Produse P ON FP.idProdus = P.idProdus
        WHERE  P.denumireProdus = 'Shaorma' AND FP.pret = 25

DROP VIEW facturiShaorma;

SELECT * FROM facturiShaorma;


CREATE FUNCTION statsFacturi()
    RETURNS @statsFacturi TABLE (Luna INT, NumeAgent VARCHAR(50), PrenumeAgent VARCHAR(50), ValoareaTotala INT)
AS
    BEGIN
        INSERT INTO @statsFacturi (Luna, NumeAgent, PrenumeAgent, ValoareaTotala)
        SELECT
            MONTH(F.dataEmitere) AS Luna,
            A.nume AS NumeAgent,
            A.prenume AS PrenumeAgent,
            SUM(FP.cantitate * FP.pret) AS ValoareaTotala
        FROM Facturi F
            INNER JOIN FacturaProdus FP ON F.idFactura = FP.idFactura
            INNER JOIN AgentiVanzare A ON F.idAgent = A.idAgent
        GROUP BY MONTH(F.dataEmitere), A.prenume, A.nume
        ORDER BY MONTH(F.dataEmitere), A.nume;
        RETURN;
    END;

DROP FUNCTION statsFacturi;

SELECT * FROM dbo.statsFacturi();


INSERT INTO Clienti (codFiscal, denumireClient) VALUES
(123456789, 'SC Exemplu SRL'),
(987654321, 'SC Alta Firma SRL'),
(456123789, 'SC Teste SRL');

INSERT INTO Produse (denumireProdus, unitateMasura) VALUES
('Laptop', 'bucata'),
('Shaorma', 'bucata'),
('Telefon', 'bucata'),
('Televizor', 'bucata');

INSERT INTO AgentiVanzare (nume, prenume) VALUES
('Popescu', 'Ion'),
('Ionescu', 'Maria'),
('Georgescu', 'Andrei');

INSERT INTO Facturi (dataEmitere, idClient, idAgent) VALUES
('2025-02-01', 1, 1),
('2025-02-15', 2, 2),
('2025-02-18', 3, 1);

INSERT INTO FacturaProdus (idFactura, idProdus, numarOrdine, cantitate, pret) VALUES
(1, 1, 1, 2, 3000), -- Laptop x 2 la 3000 lei fiecare
(1, 2, 2, 5, 25),   -- Shaorma x 5 la 25 lei fiecare
(2, 3, 1, 1, 2500), -- Telefon x 1 la 2500 lei
(2, 4, 2, 1, 4000), -- Televizor x 1 la 4000 lei
(3, 2, 1, 10, 30);  -- Shaorma x 10 la 30 lei fiecare



