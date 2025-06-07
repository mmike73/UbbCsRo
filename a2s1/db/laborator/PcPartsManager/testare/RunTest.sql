USE [PcPartsManager]
GO

CREATE PROCEDURE runTest
(@testName VARCHAR(50))
AS
BEGIN
	DECLARE @testId INT
	SELECT @testId =TestID FROM Tests WHERE Name=@testName
	EXEC @testName @testId
END

DROP PROCEDURE runTest