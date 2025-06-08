USE [PcPartsManager];
GO

CREATE PROCEDURE readRAM
    @ramId INT
AS
BEGIN
    IF dbo.existsRAM(@ramId) = 0
    BEGIN
        RAISERROR('RAM with id %d does not exist!', 16, 1, @ramId);
        RETURN;
    END

    SELECT * FROM RamMemory WHERE ramId=@ramId;
END;
