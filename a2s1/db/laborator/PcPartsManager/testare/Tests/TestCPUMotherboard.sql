USE [PcPartsManager];
GO

CREATE PROCEDURE TestCPUMotherboard
(@TestId INT)
AS
	BEGIN
		DECLARE @t1 DATETIME,@t2 DATETIME,@t3 DATETIME
		DECLARE @noRows INT

		SELECT @noRows= NoOfRows FROM TestTables WHERE @TestId=TestID
		SET @t1=GETDATE();
		
		DELETE FROM Motherboards;
		DELETE FROM CPUs;
		DELETE FROM Manufacturers;
		DELETE FROM CPUMotherboard

		EXEC insertIntoManufacturers @TestId
		EXEC insertIntoCPUs @TestId
		EXEC insertIntoMotherboards @TestId
		EXEC insertIntoCPUsMotherboards @TestId


		SET @t2=GETDATE();
		SELECT * FROM vwCPUsMotherboards;

		SET @t3=GETDATE();
		-- test endd
		
		INSERT INTO TestRuns(Description,StartAt,EndAt)
		VALUES
		('CPUMotherboard',@t1,@t3)

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

