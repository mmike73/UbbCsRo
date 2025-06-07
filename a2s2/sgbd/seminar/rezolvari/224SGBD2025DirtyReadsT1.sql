--Dirty reads T1
USE Seminar3224SGBD2025;
BEGIN TRAN;
UPDATE Clienti SET nume='client modificat' WHERE cod_c=1;
WAITFOR DELAY '00:00:05';
ROLLBACK TRAN;
SELECT * FROM Clienti;