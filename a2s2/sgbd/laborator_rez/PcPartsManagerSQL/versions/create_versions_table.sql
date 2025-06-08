USE [pc_parts_manager];
GO

CREATE TABLE versiune (
cod_v INT PRIMARY KEY IDENTITY,
nr_versiune INT
);

INSERT INTO versiune(nr_versiune) VALUES (0);