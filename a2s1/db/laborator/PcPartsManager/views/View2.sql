CREATE VIEW vwCPUsManufacturers 
AS
	SELECT 
		m.name, p.model, p.noCores
	FROM Manufacturers m
			INNER JOIN
			CPUS p
	ON m.manufacturerId=p.manufacturerId
	WHERE noCores>4

SELECT * FROM vwCPUsManufacturers