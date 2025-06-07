CREATE TABLE IF NOT EXISTS routes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    departure VARCHAR(100) NOT NULL,
    arrival VARCHAR(100) NOT NULL,
    UNIQUE KEY (departure, arrival)
);

INSERT IGNORE INTO routes (departure, arrival) VALUES
('Bistrita Nord', 'Cluj-Napoca'),
('Beclean pe Somes', 'Dej'),
('Beclean pe Somes', 'Gherla'),
('Iasi', 'Cluj-Napoca'),
('Budapesta', 'Cluj-Napoca'),
('Viena', 'Budapesta'),
('Viena', 'Munchen');

CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nume VARCHAR(50) NOT NULL,
    prenume VARCHAR(50) NOT NULL,
    telefon VARCHAR(20),
    email VARCHAR(100) UNIQUE NOT NULL
);

INSERT INTO users (nume, prenume, telefon, email) VALUES
('Danut', 'Giovani', '0712345678', 'danutgiovani@example.com'),
('Fazan', 'Gigi', '0712345678', 'gigifazan@example.com'),
('Ursu', 'Nicu', '0712345678', 'nicuursu@example.com'),
('Lupu', 'Lica', '0712345678', 'licalupu@example.com'),
('Roka', 'Indigo', '0712345678', 'indigoroka@example.com'),
('Feriga', 'Sentiment', '0712345678', 'sentimentferiga@example.com');

CREATE TABLE records (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    status ENUM('active', 'inactive') DEFAULT 'active'
);

INSERT INTO records (name, email, status) VALUES
('Danut Giovani', 'danutgiovani@example.com', 'active'),
('Fazan Gigi', 'gigifazan@example.com', 'inactive'),
('Ursu Nicu', 'nicuursu@example.com', 'active'),
('Lupu Lica', 'licalupu@example.com', 'inactive'),
('Roka Indigo', 'indigoroka@example.com', 'active'),
('Feriga Sentiment', 'sentimentferiga@example.com', 'inactive');

CREATE DATABASE it_store_simple;
USE it_store_simple;

CREATE TABLE products (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    price DECIMAL(10,2) NOT NULL,
    manufacturer VARCHAR(100),
    processor VARCHAR(100),
    memory VARCHAR(50),
    storage VARCHAR(50),
    video_card VARCHAR(100)
);

-- Sample data
INSERT INTO products (name, price, manufacturer, processor, memory, storage, video_card) VALUES
('Dell Inspiron 15', 599.99, 'Dell', 'Intel Core i5', '8GB', '512GB SSD', 'Integrated'),
('HP Pavilion', 799.99, 'HP', 'Intel Core i7', '16GB', '1TB HDD', 'NVIDIA GeForce GTX 1650'),
('Lenovo IdeaPad', 499.99, 'Lenovo', 'Intel Core i3', '4GB', '256GB SSD', 'Integrated'),
('Asus VivoBook', 699.99, 'Asus', 'AMD Ryzen 5', '8GB', '512GB SSD', 'NVIDIA GeForce GTX 1050'),
('Acer Aspire 5', 549.99, 'Acer', 'AMD Ryzen 3', '8GB', '256GB SSD', 'Integrated'),
('Dell XPS 15', 1299.99, 'Dell', 'Intel Core i7', '16GB', '1TB HDD', 'AMD Radeon RX 5500'),
('HP Omen', 1099.99, 'HP', 'AMD Ryzen 7', '32GB', '2TB HDD', 'NVIDIA GeForce GTX 1650');