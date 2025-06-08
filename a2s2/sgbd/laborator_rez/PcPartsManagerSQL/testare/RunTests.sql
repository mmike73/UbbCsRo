USE [PcPartsManager]
GO

DELETE FROM TestRuns

DELETE FROM CPUMotherboard
DELETE FROM CPUs
DELETE FROM Motherboards
DELETE FROM Manufacturers

EXEC runTest 'TestManufacturers'
EXEC runTest 'TestCPUs' 
EXEC runTest 'TestCPUMotherboard'

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews
SELECT * FROM CPUMotherboard

EXEC getAllTestRunDetails
