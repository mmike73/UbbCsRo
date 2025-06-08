USE [PcPartsManager]
GO

CREATE PROCEDURE insertIntoTestViews
    @TestID INT,
    @ViewID INT
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM TestViews WHERE TestID = @TestID AND ViewID = @ViewID)
    BEGIN
        INSERT INTO TestViews (TestID, ViewID)
        VALUES (@TestID, @ViewID);
    END
END;
GO
