USE master

CREATE DATABASE GestiuneAuto;
GO

USE GestiuneAuto

CREATE TABLE Masini(
	id_masina INT PRIMARY KEY IDENTITY(1, 1),
	id_colectie INT FOREIGN KEY REFERENCES TipColectie(id_colectie),
	marca VARCHAR(20),
	model VARCHAR(20),
	an_fabr INT,
	valoare INT,
	proprietar VARCHAR(20)
);

CREATE TABLE TipColectie(
	id_colectie INT PRIMARY KEY IDENTITY(1, 1),
	nume VARCHAR(20) UNIQUE,
	categorie VARCHAR(20)
);


INSERT INTO TipColectie(nume, categorie)
VALUES
('classicold', 'pre 50s'),
('sportold', 'pre50s'),
('raceold', 'pre50s'),
('conceptold', 'pre50s'),
('classicpunk', '60s-80s'),
('sportpunk', '60s-80s'),
('racepunk', '60s-80s'),
('conceptpunk', '60s-80s'),
('classicmodern', 'modern'),
('sportmodern', 'modern'),
('racemodern', 'modern'),
('conceptmodern', 'modern');

INSERT INTO TipColectie(nume, categorie)
VALUES
('classicinterbelic', 'interbelic'),
('raceinterbelic', 'interbelic');


INSERT INTO Masini(id_colectie, marca, 	model, 	an_fabr, valoare, proprietar)
VALUES
(6, 'bmw', '320', 1940, 1000000, 'Vasile'),
(6, 'mercedes', '180', 1930, 1200000, 'Mihai'),
(10, 'vw', 'beattle', 1940, 1000000, 'Vasile'),
(8, 'bentley', 'continental', 1932, 5000000, 'Ion'),
(16, 'mercedes', 'mclaren slr', 2007, 1000000, 'Vasile'),
(16, 'bmw', 'M1', 1990, 600000, 'Mihai'),
(6, 'bmw', '320', 1940, 1000000, 'Ion');

INSERT INTO Masini(id_colectie, marca, 	model, 	an_fabr, valoare, proprietar)
VALUES
(18, 'aston martin', '320', 1930, 1000000, 'Vasile'),
(19, 'rolls royce', 'wraith', 1928, 1000000, 'Vasile'),
(18, 'rolls royce', 'phantom', 1925, 1000000, 'Vasile'),
(19, 'bmw', '199', 1939, 1000000, 'Vasile');


SELECT
	AVG(M.valoare) AS val_medie,
	C.nume AS nume_colectie
FROM
	TipColectie C
	INNER JOIN Masini M ON M.id_colectie = C.id_colectie
GROUP BY
	C.nume
HAVING
	AVG(M.valoare) > 1000000;

SELECT
	MAX(M.valoare) AS val_max,
	C.nume AS nume_colectie,
	C.categorie AS cat_istorica,
	M.model AS model_cel_mai_cel
FROM
	TipColectie C
	INNER JOIN Masini M ON M.id_colectie = C.id_colectie
WHERE
	C.categorie = 'interbelic'
GROUP BY
	C.nume, C.categorie, M.model
	


CREATE INDEX index_masini ON Masini(marca, model);

SELECT model, marca FROM Masini WHERE marca = 'bmw';

SELECT model, marca FROM Masini WHERE model = '320';
