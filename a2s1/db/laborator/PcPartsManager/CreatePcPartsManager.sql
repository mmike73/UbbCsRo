
USE [master]
GO

CREATE DATABASE [PcPartsManager];
GO
USE [PcPartsManager];
GO

CREATE TABLE Manufacturers
(manufacturerId INT PRIMARY KEY IDENTITY(1,1),
name VARCHAR(50)
);
GO


CREATE TABLE CPUs(
cpuId INT PRIMARY KEY IDENTITY(1,1),
manufacturerId INT FOREIGN KEY REFERENCES Manufacturers(manufacturerId) ON DELETE CASCADE,
model VARCHAR(50),
baseClock FLOAT,
boostClock FLOAT,
socket VARCHAR(50),
noCores SMALLINT,
noThreads SMALLINT,
fabricationTehnologyNm TINYINT,
powerW SMALLINT,
price SMALLINT
);
GO

CREATE TABLE Motherboards(
motherboardId INT PRIMARY KEY IDENTITY(1,1),
manufacturerId INT FOREIGN KEY REFERENCES Manufacturers(manufacturerId) ON DELETE CASCADE,
model VARCHAR(50),
boardFormat VARCHAR(50),
chipset VARCHAR(50),
socket VARCHAR(50),
ramType VARCHAR(10),
maximumMemorySize SMALLINT,
pciEGeneration FLOAT,
integratedNetworkCard BIT,
bloetooth BIT,
price SMALLINT
);
GO

CREATE TABLE CPUMotherboard(
cpuId INT FOREIGN KEY REFERENCES CPUs(cpuId) ON DELETE CASCADE,
motherboardId INT FOREIGN KEY REFERENCES Motherboards(motherboardId),
PRIMARY KEY (cpuId, motherboardId)
);
GO

CREATE TABLE RamMemory(
ramId INT PRIMARY KEY IDENTITY(1,1),
manufacturerId INT FOREIGN KEY REFERENCES Manufacturers(manufacturerId) ON DELETE CASCADE,
model VARCHAR(50),
type VARCHAR(10),
stickFormat VARCHAR(10),
sizeGb SMALLINT,
configuration VARCHAR(50),
frequency SMALLINT,
latency VARCHAR(50),
price SMALLINT
);
GO

CREATE TABLE MotherboardRamMemory(
motherboardId INT FOREIGN KEY REFERENCES Motherboards(motherboardId) ON DELETE CASCADE,
ramId INT FOREIGN KEY REFERENCES RamMemory(ramId),
PRIMARY KEY (motherboardId, ramId)
);
GO

CREATE TABLE ExternalMemory(
memoryId INT PRIMARY KEY IDENTITY(1,1),
manufacturerId INT FOREIGN KEY REFERENCES Manufacturers(manufacturerId) ON DELETE CASCADE,
model VARCHAR(50),
memoryCategory VARCHAR(50),
interface VARCHAR(50),
sizeTb SMALLINT,
readSpeed SMALLINT,
writeSpeed SMALLINT,
price SMALLINT
);
GO

CREATE TABLE GPUs(
gpuId INT PRIMARY KEY IDENTITY(1,1),
manufacturerId INT FOREIGN KEY REFERENCES Manufacturers(manufacturerId) ON DELETE CASCADE,
model VARCHAR(50), 
slot VARCHAR(10),
vramType VARCHAR(10),
sizeGb INT,
baseClock INT,
boostClock INT,
memoryBus INT,
powerW SMALLINT,
price SMALLINT
);
GO

CREATE TABLE PowerSupplies(
powerSupplyId INT PRIMARY KEY IDENTITY(1,1),
manufacturerId INT FOREIGN KEY REFERENCES Manufacturers(manufacturerId) ON DELETE CASCADE,
model VARCHAR(50),
powerW INT,
certificate VARCHAR(20),
price SMALLINT
);
GO

CREATE TABLE Cases(
caseId INT PRIMARY KEY IDENTITY(1,1),
manufacturerId INT FOREIGN KEY REFERENCES Manufacturers(manufacturerId) ON DELETE CASCADE,
model VARCHAR(50),
type VARCHAR(50),
price SMALLINT
);
GO

CREATE TABLE Builds(
buildId INT PRIMARY KEY IDENTITY(1,1),
name VARCHAR(50),
cpuId INT FOREIGN KEY REFERENCES CPUs(cpuId) ON DELETE CASCADE,
motherboardId INT FOREIGN KEY REFERENCES Motherboards(motherboardId),
ramId INT FOREIGN KEY REFERENCES RamMemory(ramId),
memoryId INT FOREIGN KEY REFERENCES ExternalMemory(memoryId),
gpuId INT FOREIGN KEY REFERENCES GPUs(gpuId),
powerSupplyId INT FOREIGN KEY REFERENCES PowerSupplies(powerSupplyId),
caseId INT FOREIGN KEY REFERENCES Cases(caseId)
);
GO

/*
Msg 1785, Level 16, State 0, Line 48
Introducing FOREIGN KEY constraint 'FK__CPUMother__mothe__1332DBDC' on table 'CPUMotherboard' may cause cycles or multiple cascade paths. Specify ON DELETE NO ACTION or ON UPDATE NO ACTION, or modify other FOREIGN KEY constraints.
Msg 1750, Level 16, State 1, Line 48
Could not create constraint or index. See previous errors.
Msg 1785, Level 16, State 0, Line 69
Introducing FOREIGN KEY constraint 'FK__Motherboa__ramId__19DFD96B' on table 'MotherboardRamMemory' may cause cycles or multiple cascade paths. Specify ON DELETE NO ACTION or ON UPDATE NO ACTION, or modify other FOREIGN KEY constraints.
Msg 1750, Level 16, State 1, Line 69
Could not create constraint or index. See previous errors.
Msg 1785, Level 16, State 0, Line 123
Introducing FOREIGN KEY constraint 'FK__Builds__motherbo__29221CFB' on table 'Builds' may cause cycles or multiple cascade paths. Specify ON DELETE NO ACTION or ON UPDATE NO ACTION, or modify other FOREIGN KEY constraints.
Msg 1750, Level 16, State 1, Line 123
Could not create constraint or index. See previous errors.

Completion time: 2024-12-01T16:15:31.7059508+02:00
*/


use master
GO
if exists(select * from master.sys.databases where name ='examen')
	drop database examen
create database examen
go
use examen

CREATE TABLE tipuri_tren
(
descriere varchar(256),
id int NOT NULL PRIMARY KEY

);

CREATE TABLE trenuri
(
	id int NOT NULL PRIMARY KEY,
	nume varchar(256),
	id_tip int
);

ALTER TABLE trenuri  WITH CHECK ADD  CONSTRAINT [FK_tren_tip] FOREIGN KEY(id_tip)
REFERENCES [tipuri_tren] ([id])

CREATE TABLE trasee
(
	id int NOT NULL PRIMARY KEY,
	nume varchar(256),
	id_tren int
);
ALTER TABLE trasee  WITH CHECK ADD  CONSTRAINT [FK_tren_traseu] FOREIGN KEY(id_tren)
REFERENCES [trenuri] ([id])

CREATE TABLE statii
(
	id int NOT NULL PRIMARY KEY,
	nume varchar(256),
);

CREATE TABLE orare
(
	traseu_id int ,
	statie_id int ,
	ora_plecare time NOT NULL ,
	ora_sosire time NOT NULL ,
	primary key (traseu_id, statie_id),
	
);
ALTER TABLE orare  WITH CHECK ADD  CONSTRAINT [FK_orar_statie1] FOREIGN KEY(statie_id)
REFERENCES [statii] ([id])
ALTER TABLE orare  WITH CHECK ADD  CONSTRAINT [FK_traseu_orar1] FOREIGN KEY(traseu_id)
REFERENCES [trasee] ([id])
GO
create procedure proc1 
@traseuId int,
@statieId int,
@oraSosire time,
@oraPlecare time
as
begin
	if exists(select * from orare where traseu_id =@traseuId and statie_id=@statieId )
		begin
			UPDATE orare
			SET ora_plecare=@oraPlecare,ora_sosire=@oraSosire
			WHERE traseu_id =@traseuId and statie_id=@statieId;
		end
	else
	begin
		INSERT INTO orare
		VALUES (@traseuId,@statieId,@oraPlecare,@oraSosire);

	end
	PRINT 'proc created'
end
GO


CREATE VIEW view1 AS
select trasee.nume
from (
	SELECT traseu_id
	FROM (select traseu_id, count(statie_id) as count1  from orare group by traseu_id) t1
	WHERE t1.count1=(select count(*) from statii)) t2,trasee
where t2.traseu_id=trasee.id

go


CREATE FUNCTION f1 (@tim time)
RETURNS @tab TABLE
   (
    statie_id int,
	count1 int,
	ora_plecare time
   )
AS
BEGIN
	insert into @tab
			select statie_id,count(id_tren) as count1,ora_plecare 

			from orare join trasee on orare.traseu_id=trasee.id

			where ora_plecare=@tim
			group by statie_id,ora_plecare
			having count(id_tren)>1
	return 
	
END;
GO

/*[use examen] select * from f1('1:1:1')  */
ALTER FUNCTION Punctaj
(	
	@JucatorID int
)
RETURNS TABLE 
AS
RETURN 
(
	SELECT Castigator, Nume, (SUM(Puncte1) + Punctaj) AS P, (SUM(Valoare1) + Valoare) AS V
	FROM Partide inner join Jucatori on Jucatori.ID = Castigator
	WHERE Castigator = @JucatorID
	GROUP BY Castigator, Nume, Punctaj, Valoare

)

GO


ALTER PROCEDURE AdaugaPartida
	@TurneuID nvarchar(50), 
	@Jucator1ID nvarchar(50),
	@Jucator2ID nvarchar(50),
	@Puncte1 int,
	@Puncte2 int,
	@Valoare1 int,
	@Valoare2 int,
	@CastigatorID nvarchar(50),
	@ArenaID int,
	@Data datetime
AS
BEGIN
	INSERT INTO Partide VALUES (@Jucator1ID, @Jucator2ID, @ArenaID, @TurneuID, @Data, @CastigatorID, @Puncte1, @Puncte2, @Valoare1, @Valoare2)
END
GO

CREATE VIEW Castigatori
AS
SELECT TOP (100) PERCENT dbo.Jucatori.Nume, COUNT(*) AS NR
FROM     dbo.Jucatori INNER JOIN
                  dbo.Partide ON (dbo.Jucatori.ID = dbo.Partide.Jucator1 OR
                  dbo.Jucatori.ID = dbo.Partide.Jucator2 OR
                  dbo.Jucatori.ID = dbo.Partide.Castigator) AND dbo.Jucatori.ID = dbo.Partide.Castigator
GROUP BY dbo.Jucatori.Nume
ORDER BY NR DESC

create view view1
as
select DISTINCT nume, COUNT(*) as Numar_inchirieri from Angajati a
join Marci m on m.denumire = 'Audi'
join Evidenta e on e.id_angajat = a.id and month(data_inchiriere) = 1
group by nume


CREATE DATABASE [MersTrenuri];
GO;

USE [MersTrenuri];
GO;

CREATE TABLE Trenuri (
    idTren INT PRIMARY KEY IDENTITY(1, 1),
    numeTren VARCHAR(50),
    idTip INT FOREIGN KEY REFERENCES TipuriTrenuri(idTip)
);

CREATE TABLE TipuriTrenuri (
    idTip INT PRIMARY KEY IDENTITY(1, 1),
    descriereTip VARCHAR(50) unique
);

CREATE TABLE Statii (
    idStatie INT PRIMARY KEY IDENTITY(1, 1),
    numeStatie VARCHAR(50) UNIQUE
);

CREATE TABLE Rute (
    idRuta INT PRIMARY KEY IDENTITY (1, 1),
    numeRuta VARCHAR(50) UNIQUE,
    idTren INT FOREIGN KEY REFERENCES Trenuri(idTren)
);

CREATE TABLE StatiiRute (
    idRuta INT FOREIGN KEY REFERENCES Rute(idRuta),
    idStatie INT FOREIGN KEY REFERENCES Statii(idStatie),
    PRIMARY KEY (idRuta, idStatie),
    oraSosire TIME NOT NULL ,
    oraPlecare TIME NOT NULL ,
);

INSERT INTO TipuriTrenuri (descriereTip)
VALUES
    ('marfar'),
    ('pasageri'),
    ('maglev'),
    ('sageata'),
    ('mocanita');

INSERT INTO Trenuri (numeTren, idTip)
VALUES
    ('Thomas', 1),
    ('Frankie', 2),
    ('WidowMaker', 3),
    ('GraveDigger', 4);

INSERT INTO Statii (numeStatie)
VALUES
    ('Bistrita'),
    ('Beclean'),
    ('Gherla'),
    ('Dej'),
    ('Apahida'),
    ('Cluj'),
    ('Tokyo'),
    ('Deva');


INSERT INTO Rute(numeRuta, idTren)
VALUES
    ('Joy', 1),
    ('Glory', 2),
    ('Clujanu', 3),
    ('Niohatza', 4);

INSERT INTO StatiiRute(idRuta, idStatie, oraSosire, oraPlecare)
VALUES
    (1,1,'10:00', '10:15'),
    (1,2,'11:00', '11:15'),
    (1,3,'12:00', '12:15'),
    (1,4,'13:00', '13:15');

INSERT INTO StatiiRute(idRuta, idStatie, oraSosire, oraPlecare)
VALUES
    (2,4,'10:00', '10:15'),
    (2,5,'11:00', '11:15'),
    (2,6,'12:00', '12:15'),
    (2,7,'13:00', '13:15');

CREATE PROCEDURE AdaugaStatiiRuta
    @idRuta INT,
    @idStatie INT,
    @sosire TIME,
    @plecare TIME
AS
    BEGIN
        IF (EXISTS(SELECT * FROM StatiiRute WHERE idStatie = @idStatie AND idRuta = @idRuta))
            UPDATE StatiiRute SET oraPlecare = @plecare, oraSosire = @sosire WHERE idRuta = @idRuta AND idStatie=@idStatie;
        ELSE
            INSERT INTO StatiiRute(idRuta, idStatie, oraSosire, oraPlecare)
            VALUES (@idRuta, @idStatie, @sosire, @plecare);

    END;

EXEC AdaugaStatiiRuta @idRuta=1, @idStatie=1, @sosire='22:30', @plecare='23:00';
EXEC AdaugaStatiiRuta @idRuta=1, @idStatie=2, @sosire='22:30', @plecare='23:00';
EXEC AdaugaStatiiRuta @idRuta=1, @idStatie=3, @sosire='22:30', @plecare='23:00';
EXEC AdaugaStatiiRuta @idRuta=1, @idStatie=4, @sosire='22:30', @plecare='23:00';
EXEC AdaugaStatiiRuta @idRuta=1, @idStatie=5, @sosire='22:30', @plecare='23:00';
EXEC AdaugaStatiiRuta @idRuta=1, @idStatie=6, @sosire='12:30', @plecare='13:00';
EXEC AdaugaStatiiRuta @idRuta=1, @idStatie=7, @sosire='12:30', @plecare='13:00';
EXEC AdaugaStatiiRuta @idRuta=1, @idStatie=8, @sosire='12:30', @plecare='13:00';

EXEC AdaugaStatiiRuta @idRuta=2, @idStatie=1, @sosire='22:30', @plecare='23:00';
EXEC AdaugaStatiiRuta @idRuta=2, @idStatie=2, @sosire='22:30', @plecare='23:00';
EXEC AdaugaStatiiRuta @idRuta=2, @idStatie=3, @sosire='12:30', @plecare='13:00';
EXEC AdaugaStatiiRuta @idRuta=2, @idStatie=8, @sosire='12:30', @plecare='13:00';

SELECT * FROM StatiiRute;


CREATE VIEW vw_RuteToateStatiile
AS
    SELECT
        r1.idRuta AS IdRuta,
        r1.idStatie AS IdStatie,
        r1.oraSosire AS OraSosire,
        r1.oraPlecare AS OraPlecare
    FROM
        StatiiRute r1
    WHERE
        (SELECT COUNT(DISTINCT idStatie)
         FROM StatiiRute r2
         WHERE r1.idRuta = r2.idRuta) = (SELECT COUNT(*) FROM Statii);

CREATE VIEW vw_RuteToateStatiileGood
AS
    SELECT
        R.idRuta AS IdRuta,
        R.numeRuta AS NumeRuta
    FROM
        Rute R
    WHERE
        (SELECT COUNT(*) FROM StatiiRute WHERE idRuta = R.idRuta) = (SELECT COUNT(*) FROM Statii);



SELECT * FROM vw_RuteToateStatiileGood;