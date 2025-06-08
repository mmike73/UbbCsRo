USE [PcPartsMAnager]
GO

CREATE PROCEDURE createManufacturer
    @name VARCHAR(100)
AS
BEGIN
    DECLARE @Errors NVARCHAR(MAX);

    SET @Errors = dbo.validateManufacturer(
        @name
    )
     
    IF LEN(@Errors) > 0
    BEGIN 
        RAISERROR(@Errors, 16, 1);
        RETURN;
    END

    INSERT INTO Manufacturers (name) VALUES (@name);

    PRINT CONCAT('Added Manufacturer ', @name);
END;