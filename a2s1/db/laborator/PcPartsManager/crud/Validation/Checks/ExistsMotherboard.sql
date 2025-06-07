USE [PcPartsManager];
GO

CREATE FUNCTION existsMotherboard
(
    @id INT
)
RETURNS BIT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Motherboards WHERE motherboardId=@id)
        RETURN 1
    RETURN 0
END;