-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Gazdă: 127.0.0.1
-- Timp de generare: iun. 05, 2025 la 09:50 PM
-- Versiune server: 10.4.32-MariaDB
-- Versiune PHP: 8.0.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Bază de date: `php`
--
CREATE DATABASE IF NOT EXISTS `php` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `php`;

-- --------------------------------------------------------

--
-- Structură tabel pentru tabel `materii`
--

CREATE TABLE `materii` (
  `id` int(11) NOT NULL,
  `nume` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Eliminarea datelor din tabel `materii`
--

INSERT INTO `materii` (`id`, `nume`) VALUES
(1, 'Matematica'),
(2, 'Fizica'),
(3, 'Informatica');

-- --------------------------------------------------------

--
-- Structură tabel pentru tabel `note`
--

CREATE TABLE `note` (
  `id` int(11) NOT NULL,
  `student_id` int(11) DEFAULT NULL,
  `materie_id` int(11) DEFAULT NULL,
  `profesor_id` int(11) DEFAULT NULL,
  `nota` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Eliminarea datelor din tabel `note`
--

INSERT INTO `note` (`id`, `student_id`, `materie_id`, `profesor_id`, `nota`) VALUES
(1, 1, 1, 1, 8.5),
(2, 1, 2, 2, 7),
(3, 2, 1, 1, 9),
(4, 3, 3, 1, 10),
(5, 2, 1, 1, 10),
(6, 1, 2, 1, 10);

-- --------------------------------------------------------

--
-- Structură tabel pentru tabel `poze`
--

CREATE TABLE `poze` (
  `id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `filename` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Eliminarea datelor din tabel `poze`
--

INSERT INTO `poze` (`id`, `user_id`, `filename`) VALUES
(1, 1, '6840c1a8bea92.jpg');

-- --------------------------------------------------------

--
-- Structură tabel pentru tabel `produse`
--

CREATE TABLE `produse` (
  `id` int(11) NOT NULL,
  `nume` varchar(100) DEFAULT NULL,
  `descriere` text DEFAULT NULL,
  `pret` decimal(10,2) DEFAULT NULL,
  `stoc` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Eliminarea datelor din tabel `produse`
--

INSERT INTO `produse` (`id`, `nume`, `descriere`, `pret`, `stoc`) VALUES
(1, 'Telefon', 'Telefon mobil cu ecran de 6 inch', 999.99, 10),
(2, 'Laptop', 'Laptop performant pentru munca si jocuri', 2999.50, 5),
(3, 'Castile', 'Casti wireless cu anulare zgomot', 199.99, 20),
(4, 'Tableta', 'Tableta de 10 inch cu procesor puternic', 1500.00, 7),
(5, 'Mouse', 'Mouse optic cu fir', 50.00, 50),
(6, 'Tastatura', 'Tastatura mecanica RGB', 300.00, 15),
(7, 'Monitor', 'Monitor 24 inch Full HD', 700.00, 8),
(8, 'Imprimanta', 'Imprimanta color multifunctionala', 450.00, 3);

-- --------------------------------------------------------

--
-- Structură tabel pentru tabel `profesori`
--

CREATE TABLE `profesori` (
  `id` int(11) NOT NULL,
  `username` varchar(50) DEFAULT NULL,
  `parola` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Eliminarea datelor din tabel `profesori`
--

INSERT INTO `profesori` (`id`, `username`, `parola`) VALUES
(1, 'profesor1', 'parola123'),
(2, 'profesor2', 'secret456');

-- --------------------------------------------------------

--
-- Structură tabel pentru tabel `studenti`
--

CREATE TABLE `studenti` (
  `id` int(11) NOT NULL,
  `nume` varchar(100) DEFAULT NULL,
  `email` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Eliminarea datelor din tabel `studenti`
--

INSERT INTO `studenti` (`id`, `nume`, `email`) VALUES
(1, 'Ion Popescu', 'ion.popescu@example.com'),
(2, 'Maria Ionescu', 'maria.ionescu@example.com'),
(3, 'Alexandru Vasile', 'alexandru.vasile@example.com');

-- --------------------------------------------------------

--
-- Structură tabel pentru tabel `trenuri`
--

CREATE TABLE `trenuri` (
  `id` int(11) NOT NULL,
  `nr_tren` varchar(10) DEFAULT NULL,
  `tip_tren` varchar(20) DEFAULT NULL,
  `localitate_plecare` varchar(100) DEFAULT NULL,
  `localitate_sosire` varchar(100) DEFAULT NULL,
  `ora_plecare` time DEFAULT NULL,
  `ora_sosire` time DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Eliminarea datelor din tabel `trenuri`
--

INSERT INTO `trenuri` (`id`, `nr_tren`, `tip_tren`, `localitate_plecare`, `localitate_sosire`, `ora_plecare`, `ora_sosire`) VALUES
(1, 'IR101', 'InterRegio', 'Bucuresti', 'Brasov', '08:00:00', '10:00:00'),
(2, 'IR102', 'InterRegio', 'Brasov', 'Cluj-Napoca', '11:00:00', '14:30:00'),
(3, 'R201', 'Regio', 'Bucuresti', 'Ploiesti', '09:00:00', '10:00:00'),
(4, 'R202', 'Regio', 'Ploiesti', 'Brasov', '10:15:00', '12:15:00'),
(5, 'IR103', 'InterRegio', 'Bucuresti', 'Cluj-Napoca', '07:00:00', '13:00:00'),
(6, 'R203', 'Regio', 'Brasov', 'Sibiu', '13:00:00', '16:00:00'),
(7, 'IR104', 'InterRegio', 'Cluj-Napoca', 'Timisoara', '15:00:00', '20:00:00'),
(8, 'R204', 'Regio', 'Sibiu', 'Timisoara', '16:30:00', '21:30:00'),
(9, 'R205', 'Regio', 'Bucuresti', 'Pitesti', '06:30:00', '08:00:00'),
(10, 'R206', 'Regio', 'Pitesti', 'Craiova', '08:30:00', '10:30:00'),
(11, 'IR105', 'InterRegio', 'Craiova', 'Timisoara', '11:00:00', '16:00:00');

-- --------------------------------------------------------

--
-- Structură tabel pentru tabel `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `username` varchar(50) NOT NULL,
  `parola` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Eliminarea datelor din tabel `users`
--

INSERT INTO `users` (`id`, `username`, `parola`) VALUES
(1, 'Gabriel', '$2y$10$nJr0tZIBqiNacuPnduLZ1.IFVz97ozs24ic0rT9EByI.0yqE8jxFq');

-- --------------------------------------------------------

--
-- Structură tabel pentru tabel `utilizatori`
--

CREATE TABLE `utilizatori` (
  `id` int(11) NOT NULL,
  `username` varchar(50) DEFAULT NULL,
  `parola` varchar(255) DEFAULT NULL,
  `email` varchar(100) DEFAULT NULL,
  `token` varchar(100) DEFAULT NULL,
  `activat` tinyint(1) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Eliminarea datelor din tabel `utilizatori`
--

INSERT INTO `utilizatori` (`id`, `username`, `parola`, `email`, `token`, `activat`) VALUES
(8, 'Gabriel', 'parola', 'mihaligabriel05@gmail.com', 'c741eb0cfd800c94d0b6d028fb5f8876', 1);

--
-- Indexuri pentru tabele eliminate
--

--
-- Indexuri pentru tabele `materii`
--
ALTER TABLE `materii`
  ADD PRIMARY KEY (`id`);

--
-- Indexuri pentru tabele `note`
--
ALTER TABLE `note`
  ADD PRIMARY KEY (`id`),
  ADD KEY `student_id` (`student_id`),
  ADD KEY `materie_id` (`materie_id`),
  ADD KEY `profesor_id` (`profesor_id`);

--
-- Indexuri pentru tabele `poze`
--
ALTER TABLE `poze`
  ADD PRIMARY KEY (`id`),
  ADD KEY `user_id` (`user_id`);

--
-- Indexuri pentru tabele `produse`
--
ALTER TABLE `produse`
  ADD PRIMARY KEY (`id`);

--
-- Indexuri pentru tabele `profesori`
--
ALTER TABLE `profesori`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `username` (`username`);

--
-- Indexuri pentru tabele `studenti`
--
ALTER TABLE `studenti`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `email` (`email`);

--
-- Indexuri pentru tabele `trenuri`
--
ALTER TABLE `trenuri`
  ADD PRIMARY KEY (`id`);

--
-- Indexuri pentru tabele `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `username` (`username`);

--
-- Indexuri pentru tabele `utilizatori`
--
ALTER TABLE `utilizatori`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `username` (`username`),
  ADD UNIQUE KEY `email` (`email`);

--
-- AUTO_INCREMENT pentru tabele eliminate
--

--
-- AUTO_INCREMENT pentru tabele `materii`
--
ALTER TABLE `materii`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT pentru tabele `note`
--
ALTER TABLE `note`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT pentru tabele `poze`
--
ALTER TABLE `poze`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT pentru tabele `produse`
--
ALTER TABLE `produse`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT pentru tabele `profesori`
--
ALTER TABLE `profesori`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT pentru tabele `studenti`
--
ALTER TABLE `studenti`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT pentru tabele `trenuri`
--
ALTER TABLE `trenuri`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- AUTO_INCREMENT pentru tabele `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT pentru tabele `utilizatori`
--
ALTER TABLE `utilizatori`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- Constrângeri pentru tabele eliminate
--

--
-- Constrângeri pentru tabele `note`
--
ALTER TABLE `note`
  ADD CONSTRAINT `note_ibfk_1` FOREIGN KEY (`student_id`) REFERENCES `studenti` (`id`),
  ADD CONSTRAINT `note_ibfk_2` FOREIGN KEY (`materie_id`) REFERENCES `materii` (`id`),
  ADD CONSTRAINT `note_ibfk_3` FOREIGN KEY (`profesor_id`) REFERENCES `profesori` (`id`);

--
-- Constrângeri pentru tabele `poze`
--
ALTER TABLE `poze`
  ADD CONSTRAINT `poze_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`) ON DELETE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
