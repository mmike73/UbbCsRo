USE [PcPartsManager]
GO

CREATE PROCEDURE getTestRunTimes
AS
BEGIN
    SELECT 
        TestRunID,
        Description,
        StartAt,
        EndAt,
        DATEDIFF(SECOND, StartAt, EndAt) AS DurationInSeconds,
        CONVERT(VARCHAR, DATEADD(SECOND, DATEDIFF(SECOND, StartAt, EndAt), 0), 108) AS DurationFormatted
    FROM 
        TestRuns
END;
GO


CREATE PROCEDURE getAllTestRunDetails
AS
BEGIN
    SELECT 
        'Test Run' AS Category,
        TestRunID AS Identifier,
        Description,
        StartAt,
        EndAt,
        DATEDIFF(SECOND, StartAt, EndAt) AS DurationInSeconds,
        CONVERT(VARCHAR, DATEADD(SECOND, DATEDIFF(SECOND, StartAt, EndAt), 0), 108) AS DurationFormatted
    FROM 
        TestRuns

    SELECT 
        'View Run' AS Category,
        CAST(ViewID AS VARCHAR) AS Identifier,
        NULL AS Description,
        StartAt,
        EndAt,
        DATEDIFF(SECOND, StartAt, EndAt) AS DurationInSeconds,
        CONVERT(VARCHAR, DATEADD(SECOND, DATEDIFF(SECOND, StartAt, EndAt), 0), 108) AS DurationFormatted
    FROM 
        TestRunViews

    SELECT 
        'Table Run' AS Category,
        CAST(TableID AS VARCHAR) AS Identifier,
        NULL AS Description,
        StartAt,
        EndAt,
        DATEDIFF(SECOND, StartAt, EndAt) AS DurationInSeconds,
        CONVERT(VARCHAR, DATEADD(SECOND, DATEDIFF(SECOND, StartAt, EndAt), 0), 108) AS DurationFormatted
    FROM 
        TestRunTables
END;
GO

