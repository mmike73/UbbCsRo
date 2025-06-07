CREATE FUNCTION validateManufacturer (
    @name VARCHAR(100)
)
RETURNS NVARCHAR(MAX)
AS
BEGIN
    DECLARE @ErrorMessages NVARCHAR(MAX) = '';
    
    IF dbo.validateVarcharLength(@name, 3, 50) = 0
        SET @ErrorMessages += 'Invalid input: name of manufacturer must be between 3 and 50 characters! ';

    IF dbo.existsManufacturerWithName(@name) = 1
        SET @ErrorMessages += 'Manufacturer with name %s already exists. ';
    
    RETURN @ErrorMessages;
END