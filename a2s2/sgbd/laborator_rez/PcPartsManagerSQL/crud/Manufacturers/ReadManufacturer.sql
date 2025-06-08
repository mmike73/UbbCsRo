CREATE PROCEDURE readManufacturer
    @id INT
AS
BEGIN
    IF dbo.existsManufacturerWithId(@id) = 0
    BEGIN
        RAISERROR('Manufacturer with id %d does not exist!', 16, 1, @id);
        RETURN;
    END;

    SELECT * FROM Manufacturers WHERE manufacturerId=@id;
END;