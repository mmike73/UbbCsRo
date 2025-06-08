USE [PcPartsManager];
GO

CREATE FUNCTION existsMotherboardRamMemory
(
    @mbId INT,
    @ramId INT
)
RETURNS BIT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM MotherboardRamMemory WHERE motherboardId=@mbId AND ramId=@ramId)
        RETURN 1
    RETURN 0
END;