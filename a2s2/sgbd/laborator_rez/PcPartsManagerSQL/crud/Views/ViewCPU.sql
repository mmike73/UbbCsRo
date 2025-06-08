USE [PcPartsManager]
GO

CREATE VIEW vwCPURank
AS
SELECT 
    c.model AS CPUModel,
    c.noCores AS NumberOfCores,
    c.price AS Price
FROM 
    CPUs c
WHERE 
    c.price IS NOT NULL 
    AND c.noCores IS NOT NULL
GO




