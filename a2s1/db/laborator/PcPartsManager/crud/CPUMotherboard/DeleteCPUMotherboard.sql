USE [PcPartsManager];
GO

CREATE PROCEDURE deleteCPUMotherboard
    @cpuId INT,
    @mbId INT
AS
BEGIN
    IF dbo.existsCPUMotherboard(@cpuId, @mbId) = 0
    BEGIN 
        RAISERROR('@d - @d pair if CPU and Motherboard DOES NOT exist. ', 16, 1, @cpuId, @mbId);
        RETURN;
    END

    DELETE FROM CPUMotherboard WHERE cpuId=@cpuId AND motherboardId=@mbId;

    PRINT CONCAT('CPU - Motherboard pair with id ', @cpuId, ' and ', @mbId, ' deleted successfully');
END;