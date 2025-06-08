USE [PcPartsManager];
GO

CREATE FUNCTION validateVarcharLength
(
    @input VARCHAR(MAX),
    @minLen INT,
    @maxLen INT
)
RETURNS BIT
AS
BEGIN
    IF LEN(@input) <= @maxLen AND LEN(@input) >= @minLen
        RETURN 1;    
    RETURN 0;
END;