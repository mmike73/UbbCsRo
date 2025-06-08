USE [PcPartsManager];
GO

CREATE PROCEDURE readMotherboard
    @mbId INT
AS
BEGIN
    IF dbo.existsMotherboard(@mbId) = 0
    BEGIN
        RAISERROR('Motherboard with id %d does not exist!', 16, 1, @mbId);
        RETURN;
    END

    SELECT * FROM Motherboards WHERE motherboardId=@mbId;
END;