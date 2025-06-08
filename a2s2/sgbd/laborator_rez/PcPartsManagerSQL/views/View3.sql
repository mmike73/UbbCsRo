CREATE VIEW vwCPUsMotherboards
AS
    SELECT 
        m.model,
        m.socket, 
        COUNT(p.cpuId) as compatibleCPUs
    FROM 
        Motherboards m
    INNER JOIN 
        CPUs p ON p.socket = m.socket
    GROUP BY 
        m.model, m.socket;

SELECT * FROM vwCPUsMotherboards