CREATE PROCEDURE createCPUMotherboard
    @cpuId INT,
    @mbId INT
AS
BEGIN
    DECLARE @Errors NVARCHAR(MAX);

    SET @Errors = dbo.validateCPUMotherboard(
        @cpuId,
        @mbId
    );

    IF LEN(@Errors) > 0
    BEGIN
        RAISERROR(@Errors, 16, 1);
        RETURN;
    END

    IF dbo.existsCPUMotherboard(@cpuId, @mbId) = 1
    BEGIN
        RAISERROR('@d - @d pair if CPU and Motherboard already exists. ', 16, 2, @cpuId, @mbId);
        RETURN;
    END

    INSERT INTO CPUMotherboard(
        cpuId,
        motherboardId
    )
    VALUES (
        @cpuId,
        @mbId
    );

    PRINT CONCAT('m-m relationship between', @cpuId, ' and ', @mbId, ' added successfully');
END;