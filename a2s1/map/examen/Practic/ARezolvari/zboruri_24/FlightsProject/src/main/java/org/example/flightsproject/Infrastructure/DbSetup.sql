CREATE DATABASE [FlightsProject];
GO

USE [FlightsProject];
GO

CREATE TABLE Clients (
    clientId BIGINT PRIMARY KEY IDENTITY (1, 1),
    clientName VARCHAR(50),
    clientUsername VARCHAR(50) UNIQUE
);
GO

CREATE TABLE Flights (
    flightId BIGINT PRIMARY KEY IDENTITY (1, 1),
    fromPlace VARCHAR(50),
    toPlace VARCHAR(50),
    departureTime DATETIME,
    landingTime DATETIME,
    seats INT
);
GO

CREATE TABLE Ticket (
    username VARCHAR(50),
    flightId BIGINT FOREIGN KEY REFERENCES Flights(flightId),
    purchaseTime DATETIME,
    CONSTRAINT pk_Ticket PRIMARY KEY (username, flightId)
);
GO

INSERT INTO Clients (clientName, clientUsername) VALUES
                                                     ('John Doe', 'johndoe'),
                                                     ('Jane Smith', 'janesmith'),
                                                     ('Robert Brown', 'robertbrown'),
                                                     ('Emily White', 'emilywhite');
GO


INSERT INTO Flights (fromPlace, toPlace, departureTime, landingTime, seats) VALUES
                                                                                ('New York', 'Los Angeles', '2025-02-20 08:00:00', '2025-02-20 11:30:00', 150),
                                                                                ('London', 'Paris', '2025-02-21 12:00:00', '2025-02-21 14:00:00', 120),
                                                                                ('Berlin', 'Rome', '2025-02-22 09:00:00', '2025-02-22 11:15:00', 180),
                                                                                ('Tokyo', 'Seoul', '2025-02-23 14:30:00', '2025-02-23 16:45:00', 200);
GO

INSERT INTO Ticket (username, flightId, purchaseTime) VALUES
                                                          ('johndoe', 1, '2025-02-10 10:00:00'),
                                                          ('janesmith', 2, '2025-02-12 15:30:00'),
                                                          ('robertbrown', 3, '2025-02-13 09:45:00'),
                                                          ('emilywhite', 4, '2025-02-14 13:00:00');
GO
