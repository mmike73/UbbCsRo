USE [PcPartsManager];
GO

CREATE PROCEDURE TestManufacturers
(@TestId INT)
AS
BEGIN
	DECLARE @t1 DATETIME,@t2 DATETIME,@t3 DATETIME
	DECLARE @noRows INT
	SELECT @noRows= NoOfRows FROM TestTables WHERE @TestId=TestID
	SET @t1=GETDATE();
	
	DELETE FROM Manufacturers;
	EXEC insertIntoManufacturers @TestId
	
	SET @t2=GETDATE();
	SELECT * FROM vwManufacturers;
	SET @t3=GETDATE();
	-- test ended
	
	INSERT INTO TestRuns(Description,StartAt,EndAt)
	VALUES
	('TestManufacturers',@t1,@t3)
	DECLARE @TestRunID INT
	SELECT @TestRunID= MAX(TestRunID) FROM TestRuns
	DECLARE @ViewID INT
	SELECT @ViewID = ViewID FROM TestViews WHERE TestID=@TestId
	DECLARE @TableID INT
	SELECT @TableID = TableID FROM TestTables WHERE TestID=@TestId
	INSERT INTO TestRunViews(TestRunID,ViewID,StartAt,EndAt)
	VALUES
	(@TestRunID,@ViewID,@t2,@t3)
	INSERT INTO TestRunTables(TestRunID,TableID,StartAt,EndAt)
	VALUES
	(@TestRunID,@TableID,@t1,@t2)
END

