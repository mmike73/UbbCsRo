USE [PcPartsManager];
GO

CREATE PROCEDURE deleteMotherboardRamMemory
    @mbId INT,
    @ramId INT
AS
BEGIN
    IF dbo.existsMotherboardRamMemory(@mbId, @ramId) = 0
    BEGIN 
        RAISERROR('@d - @d pair if Motherboard and RAM DOES NOT exist. ', 16, 1, @mbId, @ramId);
        RETURN;
    END

    DELETE FROM MotherboardRamMemory WHERE motherboardId=@mbId AND ramId=@ramId;

    PRINT CONCAT('Motherboard - RAN pair with id ', @mbId, ' and ', @ramId, ' deleted successfully');
END;