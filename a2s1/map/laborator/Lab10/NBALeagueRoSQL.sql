CREATE DATABASE [NBALeagueRomania];
GO

USE [NBALeagueRomania];
GO

CREATE TABLE Teams (
	teamId INT PRIMARY KEY,
	teamName VARCHAR(50)
);
GO


CREATE TABLE Players (
	studentId INT PRIMARY KEY,
	studentName VARCHAR(50), 
	schoolName VARCHAR(50),
	teamId INT FOREIGN KEY REFERENCES Teams(teamId)
);
GO

CREATE TABLE Matches (
	teamId1 INT FOREIGN KEY REFERENCES Teams(teamId),
	teamId2 INT FOREIGN KEY REFERENCES Teams(teamId),
	matchDate  DATETIME,
	PRIMARY KEY (teamId1, teamId2)
);
GO

CREATE TABLE ActivePlayers (
	studentId INT FOREIGN KEY REFERENCES Players(studentId) ON DELETE CASCADE,
	teamId1 INT,
	teamId2 INT,
	FOREIGN KEY (teamId1, teamId2) REFERENCES Matches(teamId1, teamId2),
	score INT,
	playerType VARCHAR(10)
);
GO

DELETE FROM ActivePlayers
Select * from Players where studentId = 400