CREATE VIEW vwRAMRank 
AS
	SELECT
		model,
		type,
		sizeGb,
		configuration,
		frequency,
		price
	FROM
		RamMemory
	WHERE
		sizeGb >= 8
		AND type IN ('DDR4', 'DDR5')
		AND frequency > 3200


