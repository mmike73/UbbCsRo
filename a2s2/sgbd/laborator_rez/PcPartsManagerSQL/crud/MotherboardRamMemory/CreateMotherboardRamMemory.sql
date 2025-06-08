CREATE PROCEDURE createMotherboardRamMemory
    @mbId INT,
    @ramId INT
AS
BEGIN
    DECLARE @Errors NVARCHAR(MAX);

    SET @Errors = dbo.validateMotherboardRamMemory(
        @mbId,
        @ramId
    );

    IF LEN(@Errors) > 0
    BEGIN
        RAISERROR(@Errors, 16, 1);
        RETURN;
    END

    IF dbo.existsMotherboardRamMemory(@mbId, @ramId) = 1
    BEGIN
        RAISERROR('@d - @d pair if Motherboard and RAM already exists. ', 16, 2, @mbId, @ramId);
        RETURN;
    END

    INSERT INTO MotherboardRamMemory(
		motherboardId,
		ramId
    )
    VALUES (
        @mbId,
		@ramId
    );

    PRINT CONCAT('m-m relationship between', @mbId, ' and ', @ramId, ' added successfully');
END;