USE [PcPartsManager];
GO

CREATE FUNCTION existsRAM
(
    @id INT
)
RETURNS BIT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM RamMemory WHERE ramId=@id)
        RETURN 1
    RETURN 0
END;