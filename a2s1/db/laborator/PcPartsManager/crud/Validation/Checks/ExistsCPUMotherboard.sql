USE [PcPartsManager];
GO

CREATE FUNCTION existsCPUMotherboard
(
    @cpuId INT,
    @mbId INT
)
RETURNS BIT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM CPUMotherboard WHERE cpuId=@cpuId AND motherboardId=@mbId)
        RETURN 1
    RETURN 0
END;