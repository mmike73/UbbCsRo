USE [pc_parts_manager];
GO

CREATE PROCEDURE schimba_versiune @target INT
AS
BEGIN
	IF @target > 5 OR @target < 0
	BEGIN
		PRINT 'Versiune invalida, incearca o valoare intre 0 si 5\n';
		RETURN;
	END

    DECLARE @crt INT;

    SELECT @crt = nr_versiune FROM versiune WHERE cod_v = 1;

	PRINT 'Versiune curenta ' + CAST(@crt AS VARCHAR) + '\n'

    IF @target > @crt
    BEGIN
        WHILE @crt < @target
        BEGIN
            SET @crt = @crt + 1;

            IF @crt = 1 EXEC versiune1;
            IF @crt = 2 EXEC versiune2;
            IF @crt = 3 EXEC versiune3;
            IF @crt = 4 EXEC versiune4;
            IF @crt = 5 EXEC versiune5;
        END

        PRINT 'Trecerea la versiunea ' + CAST(@target as VARCHAR) + ' realizata cu succes\n';
    END

    ELSE IF @target < @crt
    BEGIN
        WHILE @crt > @target
        BEGIN
            IF @crt = 5 EXEC undo_versiune5;
            IF @crt = 4 EXEC undo_versiune4;
            IF @crt = 3 EXEC undo_versiune3;
            IF @crt = 2 EXEC undo_versiune2;
            IF @crt = 1 EXEC undo_versiune1;

			SET @crt = @crt - 1;

        END
        PRINT 'Trecerea la versiunea ' + CAST(@target as VARCHAR) + ' realizata cu succes\n';
    END

    ELSE
    BEGIN
        PRINT 'Ești deja la versiunea dorită!';
    END

    UPDATE versiune
    SET nr_versiune = @target
    WHERE cod_v = 1;

END

EXEC schimba_versiune @target = 0;

INSERT INTO memorie_ram (cod_producator, model, tip, format_placute, capacitate, frecventa, latenta, pret)
VALUES (1, 'XYZ123', 'DDR4', 'DIMM', 16, 3200, 'CL16', 79.99);

SELECT *
FROM memorie_ram
WHERE model = 'XYZ123';


DROP PROCEDURE schimba_versiune;
