USE [PcPartsManager]
GO

EXEC setupTestConfiguration
    @tableName = 'Manufacturers',
    @viewName = 'vwManufacturers',
    @testName = 'TestManufacturers',
    @numberOfEntries = 1000;

EXEC setupTestConfiguration
    @tableName = 'CPUs',
    @viewName = 'vwCPUsManufacturers',
    @testName = 'TestCPUs',
    @numberOfEntries = 1000;
    
EXEC setupTestConfiguration
    @tableName = 'CPUMotherboard',
    @viewName = 'vwCPUsMotherboards',
    @testName = 'TestCPUMotherboards',
    @numberOfEntries = 1000;










