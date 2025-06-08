USE [PcPartsManager];
GO

CREATE PROCEDURE deleteRAM
    @ramId INT
AS
BEGIN
    IF dbo.existsRAM(@ramId) = 0
    BEGIN
        RAISERROR('RAM Memory with id %d does not exist!', 16, 1, @ramId);
        RETURN;
    END;

    DELETE FROM RamMemory WHERE ramId=@ramId;

    PRINT CONCAT('RAM with id ', @ramId, ' deleted successfully');
END;
