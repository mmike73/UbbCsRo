USE [PcPartsManager];
GO

CREATE PROCEDURE readCPU
    @cpuId INT
AS
BEGIN
    IF dbo.existsCPU(@cpuId) = 0
    BEGIN
        RAISERROR('CPU with id %d does not exist!', 16, 1, @cpuId);
        RETURN;
    END

    SELECT * FROM CPUs WHERE cpuId=@cpuId;
END;