CREATE DATABASE "GestiuneTurism";

\connect "GestiuneTurism";

CREATE TABLE "AgentiiTurism" (
                                 "agentieId" INT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
                                 "numeAgentie" VARCHAR(50) UNIQUE 
);

CREATE TABLE "Angajati" (
                            "angajatId" INT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
                            "agentieId" INT,
                            "username" VARCHAR(50),
                            "password" VARCHAR(50),
                            CONSTRAINT fk_Agentie_Angajati FOREIGN KEY ("agentieId") REFERENCES "AgentiiTurism"("agentieId")
);


CREATE TABLE "Rezervari" (
                             "rezervareId" INT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,    "numeClient" VARCHAR(50),
                             "agentieId" INT,
                             "telefon" VARCHAR(15),
                             "nrLocuriRezervate" INT,
                             CONSTRAINT "fk_Agentie_Rezervari" FOREIGN KEY ("agentieId") REFERENCES "AgentiiTurism"("agentieId")
);

CREATE TABLE "Excursii" (
                            "excursieId" INT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
                            "obiectiv" VARCHAR(50),
                            "firmaTransport" VARCHAR(50),
                            "nrLocuri" INT,
                            "pret" INT,
                            "dataOraPlecare" TIMESTAMP
);
ALTER TABLE "Rezervari" ADD COLUMN "excursieId" INT;
ALTER TABLE "Rezervari" ADD CONSTRAINT "fk_Rezervari_Excursii" FOREIGN KEY ("excursieId") REFERENCES "Excursii"("excursieId");

ALTER TABLE "Excursii" DROP COLUMN "pret";
ALTER TABLE "Excursii" ADD COLUMN "pret" INT;

ALTER TABLE "\"Angajati\""  ALTER COLUMN "\"username\"" ADD CONSTRAINT UNIQUE


DROP  TABLE "Angajati";
DROP  TABLE "Excursii";
DROP  TABLE "Rezervari";
DROP  TABLE "AgentiiTurism";



INSERT INTO "AgentiiTurism"("numeAgentie")
VALUES
    ('CHRISTIAN TOUR'),
    ('EXPLORATOR TRAVEL'),
    ('VIAJES EN MUNDO'),
    ('WANDERLUST TOURS');

INSERT INTO "Excursii"("obiectiv", "firmaTransport", "nrLocuri", "pret", "dataOraPlecare")
VALUES
    ('Paris', 'Air France', 30, 1500, '2025-06-01 08:00:00'),
    ('Rome', 'Ryanair', 50, 1200, '2025-06-10 10:00:00'),
    ('Barcelona', 'Lufthansa', 40, 1400, '2025-06-15 09:00:00'),
    ('London', 'British Airways', 35, 1600, '2025-07-01 07:30:00');

INSERT INTO "Rezervari"("numeClient", "excursieId", "agentieId", "telefon", "nrLocuriRezervate")
VALUES
    ('Alex Popescu', 1, 1, '0723456789', 2),
    ('Maria Ionescu', 2, 2, '0741234567', 1),
    ('Ion Dobre', 3, 3, '0759876543', 4),
    ('Elena Munteanu', 4, 4, '0761234567', 3);