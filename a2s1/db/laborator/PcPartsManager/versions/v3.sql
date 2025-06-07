USE [pc_parts_manager];
GO

CREATE PROCEDURE versiune3
AS
BEGIN
	CREATE TABLE monitoare (
		cod_monitor INT PRIMARY KEY IDENTITY(1, 1),
		cod_producator INT FOREIGN KEY REFERENCES producatori(cod_producator),
		model VARCHAR(10),
		diagonala_inch SMALLINT,
		rezolutie VARCHAR(10),
		rata_refresh_hz SMALLINT,
		pret SMALLINT
	);
END;
GO

CREATE PROCEDURE undo_versiune3
AS
BEGIN
	DROP TABLE monitoare;
END;
GO

EXEC versiune3;
EXEC undo_versiune3;