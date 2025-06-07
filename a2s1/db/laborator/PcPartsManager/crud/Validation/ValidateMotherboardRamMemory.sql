CREATE FUNCTION validateMotherboardRamMemory (
    @mbId INT,
    @ramId INT
)
RETURNS NVARCHAR(MAX)
AS
BEGIN
    DECLARE @ErrorMessage NVARCHAR(MAX) = '';

    IF @mbId IS NULL SET @ErrorMessage += 'Motherboard ID cannot be null. ';
    IF @ramId IS NULL SET @ErrorMessage += 'RAM ID cannot be null. ';

    IF dbo.existsMotherboard(@mbId) = 0
        SET @ErrorMessage += CONCAT('Motherboard with id ', @mbId, ' does not exist!');

    IF dbo.existsRAM(@ramId) = 0
        SET @ErrorMessage += CONCAT('RAM with id ', @ramId, ' does not exist!');

    RETURN @ErrorMessage;
END;