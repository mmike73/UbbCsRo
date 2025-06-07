USE [PcPartsManager]
GO

CREATE PROCEDURE setupTestConfiguration
    @tableName NVARCHAR(255), -- Name of the table to insert
    @viewName NVARCHAR(255),  -- Name of the view to insert
    @testName NVARCHAR(255),  -- Name of the test to insert
    @numberOfEntries INT      -- Number of rows for TestTables
AS
BEGIN
    EXEC insertIntoTables @tableName;

    EXEC insertIntoViews @viewName;

    EXEC insertIntoTtests @testName;

    DECLARE @maxTestId INT, @maxViewId INT, @maxTableId INT;

    SELECT @maxTestId = ISNULL(MAX(testId), 0) FROM Tests;
    SELECT @maxViewId = ISNULL(MAX(viewId), 0) FROM Views;
    SELECT @maxTableId = ISNULL(MAX(tableId), 0) FROM Tables;

    INSERT INTO TestViews (TestId, ViewId)
    VALUES (@maxTestId, @maxViewId);

    INSERT INTO TestTables (TestId, TableId, NoOfRows, Position)
    VALUES (@maxTestId, @maxTableId, @numberOfEntries, 1);
END;
GO