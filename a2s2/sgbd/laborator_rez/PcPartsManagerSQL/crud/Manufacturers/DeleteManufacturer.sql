CREATE PROCEDURE deleteManufacturerByName
    @name VARCHAR(100)
AS
BEGIN
    IF dbo.validateVarcharLength(@name, 3, 50) = 0
    BEGIN
        RAISERROR('Invalid input: name of manufacturer must be between 3 and 50 characters!', 16, 2);
        RETURN;    
    END;

    IF dbo.existsManufacturerWithName(@name) = 0
    BEGIN
        RAISERROR('Manufacturer with name "%s" does not existst!', 16, 3, @name);
        RETURN;    
    END;

    DELETE FROM Manufacturers WHERE name=@name;
END;

CREATE PROCEDURE deleteManufacturerById
    @id INT
AS
BEGIN
    IF dbo.existsManufacturerWithId(@id) = 0
    BEGIN
        RAISERROR('Manufacturer with id %d does not exist!', 16, 1, @id);
        RETURN;    
    END;

    DELETE FROM Manufacturers WHERE manufacturerId=@id;
END;