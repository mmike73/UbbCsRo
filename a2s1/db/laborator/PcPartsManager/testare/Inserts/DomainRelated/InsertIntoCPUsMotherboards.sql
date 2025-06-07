USE [PcPartsManager]
GO

CREATE PROCEDURE insertIntoCPUsMOtherboards
    (@testId INT)
AS
BEGIN
    INSERT INTO CPUMotherboard (cpuId, motherboardId)
    SELECT
        c.cpuId,
        m.motherboardId
    FROM
        CPUs c
    INNER JOIN
        Motherboards m
    ON
        c.socket = m.socket; 
END;
GO
