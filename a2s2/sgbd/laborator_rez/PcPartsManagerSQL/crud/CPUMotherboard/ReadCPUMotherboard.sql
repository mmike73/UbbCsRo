USE [PcPartsManager];
GO

CREATE PROCEDURE readCPUMotherboard
    @cpuId INT,
    @mbId INT
AS
BEGIN
    IF dbo.existsCPUMotherboard(@cpuId, @mbId) = 0
    BEGIN 
        RAISERROR('@d - @d pair of CPU and Motherboard DOES NOT exist. ', 16, 1, @cpuId, @mbId);
        RETURN;
    END

    SELECT * FROM CPUMotherboard WHERE cpuId=@cpuId AND motherboardId=@mbId;

END;