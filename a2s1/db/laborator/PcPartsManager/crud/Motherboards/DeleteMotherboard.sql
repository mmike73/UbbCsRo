USE [PcPartsManager];
GO

CREATE PROCEDURE deleteMotherboard
    @mbId INT
AS
BEGIN
    IF dbo.existsMotherboard(@mbId) = 0
    BEGIN
        RAISERROR('Motherboard with id %d does not exist!', 16, 1, @mbId);
        RETURN;
    END

    DELETE FROM Motherboards WHERE motherboardId=@mbId;

    PRINT CONCAT('Motherboard with id ', @mbId, ' deleted successfully');
END;
