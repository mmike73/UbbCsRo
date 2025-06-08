CREATE NONCLUSTERED INDEX IX_RAM_Price_Size
ON RamMemory(price, sizeGb DESC)
INCLUDE (model, type, configuration, frequency);
GO