--Phantom reads T2
USE Seminar3224SGBD2025;
BEGIN TRAN;
INSERT INTO Clienti (nume, email, parola, data_nasterii) VALUES
('Client phantom','phantom@gmail.com','qwasdfg4253t','2000-02-02');
COMMIT TRAN;