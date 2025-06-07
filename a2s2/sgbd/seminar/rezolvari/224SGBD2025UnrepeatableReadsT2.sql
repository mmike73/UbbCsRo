--Unrepeatable reads T2
USE Seminar3224SGBD2025;
BEGIN TRAN;
UPDATE Clienti SET nume='client nou2' WHERE cod_c=2;
COMMIT TRAN;