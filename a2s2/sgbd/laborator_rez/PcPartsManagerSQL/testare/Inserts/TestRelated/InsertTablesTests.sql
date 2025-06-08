USE [PcPartsManager]
GO

CREATE PROCEDURE insertIntoTestTables
    @TestID INT,
    @TableID INT,
    @NoOfRows INT,
    @Position INT
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM TestTables WHERE TestID = @TestID AND TableID = @TableID)
    BEGIN
        INSERT INTO TestTables (TestID, TableID, NoOfRows, Position)
        VALUES (@TestID, @TableID, @NoOfRows, @Position);
    END
END;
GO
		--(1,1,1000,3),
		--(2,2,1000,1),
		--(3,3,1000,2)
