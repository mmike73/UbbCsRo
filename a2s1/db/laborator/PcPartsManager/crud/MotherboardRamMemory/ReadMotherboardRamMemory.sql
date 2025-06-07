USE [PcPartsManager];
GO

CREATE PROCEDURE readMotherboardRamMemory
    @mbId INT,
    @ramId INT
AS
BEGIN
    IF dbo.existsMotherboardRamMemory(@mbId, @ramId) = 0
    BEGIN 
        RAISERROR('@d - @d pair of Motherboard and RAM DOES NOT exist. ', 16, 1, @mbId, @ramId);
        RETURN;
    END

    SELECT * FROM MotherboardRamMemory WHERE motherboardId=@mbId AND ramId=@ramId;

END;