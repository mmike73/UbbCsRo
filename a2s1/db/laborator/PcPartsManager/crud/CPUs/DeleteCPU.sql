USE [PcPartsManager];
GO

CREATE PROCEDURE deleteCPU
    @cpuId INT
AS
BEGIN
    IF dbo.existsCPU(@cpuId) = 0
    BEGIN
        RAISERROR('CPU with id %d does not exist!', 16, 1, @cpuId);
        RETURN;
    END

    DELETE FROM CPUs WHERE cpuId=@cpuId;

    PRINT CONCAT('CPU with id ', @cpuId, ' deleted successfully');
END;