USE [PcPartsManager];
GO

CREATE FUNCTION existsManufacturerWithName
(
    @name VARCHAR(MAX)
)
RETURNS BIT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Manufacturers WHERE name=@name)
        RETURN 1
    RETURN 0
END

CREATE FUNCTION existsManufacturerWithId
(
    @id INT
)
RETURNS BIT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Manufacturers WHERE manufacturerId=@id)
        RETURN 1
    RETURN 0
END