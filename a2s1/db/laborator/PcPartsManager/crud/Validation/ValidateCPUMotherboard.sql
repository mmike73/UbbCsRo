CREATE FUNCTION validateCPUMotherboard (
    @cpuId INT,
    @mbId INT
)
RETURNS NVARCHAR(MAX)
AS
BEGIN
    DECLARE @ErrorMessage NVARCHAR(MAX) = '';

    IF @cpuId IS NULL SET @ErrorMessage += 'CPU ID cannot be null. ';
    IF @mbId IS NULL SET @ErrorMessage += 'Motherboard ID cannot be null. ';

    IF dbo.existsCPU(@cpuId) = 0
        SET @ErrorMessage += CONCAT('CPU with id ', @cpuId, ' does not exist!');

    IF dbo.existsMotherboard(@mbId) = 0
        SET @ErrorMessage += CONCAT('Motherboard with id ', @mbId, ' does not exist!');

    RETURN @ErrorMessage;
END;