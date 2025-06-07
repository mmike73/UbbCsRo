CREATE PROCEDURE updateManudacturerName
    @id INT,
    @newName VARCHAR(100)
AS
BEGIN
    IF dbo.existsManufacturerWithId(@id) = 0
    BEGIN
        RAISERROR('Manufacturer with id %d does not exist!', 16, 1, @id);
        RETURN;
    END;

    IF dbo.validateVarcharLength(@newName, 3, 50) = 0
    BEGIN
        RAISERROR('Invalid input: name of manufacturer must be between 3 and 50 characters!', 16, 2);
        RETURN;
    END;

    IF dbo.existsManufacturerWithName(@newName) = 1
    BEGIN 
        RAISERROR('Manufacturer with name "%s" already exists!', 16, 3, @newName);
        RETURN;    
    END;

    UPDATE Manufacturers SET name=@newName WHERE manufacturerId=@id;

    PRINT CONCAT('Manufacturer name of ', @id, ' updated to ', @newName);
END;