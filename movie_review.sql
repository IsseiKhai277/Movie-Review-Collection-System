-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 25, 2025 at 04:46 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `movie_review`
--

-- --------------------------------------------------------

--
-- Table structure for table `comment`
--

CREATE TABLE `comment` (
  `comment_id` int(50) NOT NULL,
  `rev_comment` varchar(500) NOT NULL,
  `movie_id` int(50) UNSIGNED NOT NULL,
  `user_id` int(11) UNSIGNED NOT NULL,
  `thumbs_count` int(50) UNSIGNED NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `comment`
--

INSERT INTO `comment` (`comment_id`, `rev_comment`, `movie_id`, `user_id`, `thumbs_count`) VALUES
(8, 'WOW this movie is good', 6, 20, 3),
(11, 'WOW this movie is good', 7, 20, 3),
(13, 'The chemistry between the male lead and female lead is great', 7, 1, 1),
(14, 'NOM NOM!', 8, 1, 2),
(15, 'The main character power is really OP', 13, 1, 1),
(16, 'The mustang design is really good', 12, 1, 0),
(17, 'I\'m not really into animation but this one is good', 8, 20, 2),
(18, 'Mannn the action scene is good', 9, 20, 1),
(19, 'Scaryyy', 6, 22, 1),
(20, 'Not really recommend for who doesnt like lovey dovey. well if its for me who like romance movie, it really makes me cryyyyyy', 7, 22, 2),
(21, 'I like anime...so yeah 5 stars', 13, 22, 1),
(24, 'wow', 6, 1, 1),
(26, 'The dinosaur looks real', 17, 1, 0),
(27, 'The dinosaur looks real', 15, 31, 1),
(28, 'Well I follow the series', 13, 31, 0),
(29, 'Whatttttt impressive', 6, 31, 1),
(30, 'The female lead looks so beautiful', 7, 31, 1),
(31, 'I like action', 9, 31, 0),
(32, 'Its boringg', 12, 31, 0),
(33, 'Monke power', 14, 31, 1),
(34, 'The finale for this francise is good', 17, 31, 0),
(35, 'Bro, the black hole looks so beautiful', 18, 33, 0),
(36, 'This movie is scary and best', 19, 33, 1);

-- --------------------------------------------------------

--
-- Table structure for table `favorites`
--

CREATE TABLE `favorites` (
  `favorite_id` int(11) NOT NULL,
  `user_id` int(11) UNSIGNED NOT NULL,
  `movie_id` int(50) UNSIGNED NOT NULL,
  `added_date` datetime(6) NOT NULL DEFAULT current_timestamp(6)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `favorites`
--

INSERT INTO `favorites` (`favorite_id`, `user_id`, `movie_id`, `added_date`) VALUES
(5, 23, 6, '2025-01-15 16:34:02.395460'),
(9, 21, 12, '2025-01-21 02:03:01.822851'),
(17, 21, 9, '2025-01-21 02:10:19.262664'),
(18, 21, 13, '2025-01-21 02:13:05.701707'),
(19, 23, 7, '2025-01-21 02:16:58.303642'),
(20, 23, 12, '2025-01-21 02:17:06.804080'),
(21, 23, 13, '2025-01-21 02:17:11.901233'),
(23, 23, 8, '2025-01-21 02:17:27.391787'),
(24, 23, 9, '2025-01-21 02:18:19.873437'),
(26, 21, 6, '2025-01-21 03:15:21.406897'),
(27, 32, 8, '2025-01-24 01:54:50.066974'),
(28, 32, 15, '2025-01-24 01:55:08.567345'),
(29, 32, 16, '2025-01-24 01:55:20.935457'),
(30, 32, 14, '2025-01-24 01:56:19.196658'),
(31, 32, 19, '2025-01-24 09:30:37.356414');

-- --------------------------------------------------------

--
-- Table structure for table `movie`
--

CREATE TABLE `movie` (
  `movie_id` int(50) UNSIGNED NOT NULL,
  `movie_name` varchar(500) NOT NULL,
  `movie_genre` varchar(100) NOT NULL,
  `duration` varchar(20) NOT NULL,
  `avg_rating` double DEFAULT NULL,
  `rating_count` int(255) DEFAULT NULL,
  `user_id` int(11) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `movie`
--

INSERT INTO `movie` (`movie_id`, `movie_name`, `movie_genre`, `duration`, `avg_rating`, `rating_count`, `user_id`) VALUES
(6, 'Inceptionss', 'Action, Mystery, Sci-Fi', '2 hours 40 minutes', 4.6, 4, 18),
(7, 'The Legend Of Blue Sea', 'Drama, Romance', '2 hours 30 minutes', 3.75, 2, 18),
(8, 'Pac-Man', 'Action, Adventure, Comedy, Family', '1 hours 40 minutes', 4.85, 2, 18),
(9, 'Hawaii Five-O', 'Action, Crime, Mystery', '2 hours 10 minutes', 4.866667, 3, 19),
(12, 'The Fast And Furious', 'Action, Crime, Family', '2 hours 50 minutes', 3.266667, 3, 24),
(13, 'In Another World I Become Slime', 'Action, Animation, Fantasy', '2 hours 10 minutes', 4.75, 4, 25),
(14, 'Rise Of Apes', 'Action, Drama, War', '2 hours 25 minutes', 5, 1, 25),
(15, 'Jurassic Park', 'Action, Adventure, Thriller', '2 hours 10 minutes', 4.3, 1, 29),
(16, 'Jurassic Park II', 'Action, Adventure, Thriller', '2 hours 42 minutes', NULL, NULL, 29),
(17, 'Jurassic Park III', 'Action, Adventure, Thriller', '2 hours 45 minutes', 4.7, 2, 29),
(18, 'Interstellar', 'Action, Biography, Sci-Fi', '2 hours 40 minutes', NULL, NULL, 30),
(19, 'Munafik', 'Action, Drama, Horror', '2 hours 40 minutes', 4.5, 1, 34);

-- --------------------------------------------------------

--
-- Table structure for table `rating`
--

CREATE TABLE `rating` (
  `rating_id` int(100) NOT NULL,
  `rating_given` double NOT NULL,
  `user_id` int(11) UNSIGNED NOT NULL,
  `movie_id` int(50) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `rating`
--

INSERT INTO `rating` (`rating_id`, `rating_given`, `user_id`, `movie_id`) VALUES
(3, 4.5, 1, 6),
(4, 4.5, 1, 7),
(5, 3, 20, 7),
(6, 4, 22, 6),
(7, 5, 1, 9),
(8, 3.5, 1, 12),
(9, 4.5, 1, 13),
(10, 5, 20, 6),
(11, 4.7, 20, 8),
(12, 4.6, 20, 9),
(13, 4.3, 20, 12),
(14, 4.8, 20, 13),
(15, 5, 22, 8),
(16, 5, 22, 13),
(18, 4.5, 1, 17),
(19, 4.3, 31, 15),
(20, 4.7, 31, 13),
(21, 4.9, 31, 6),
(22, 5, 31, 9),
(23, 2, 31, 12),
(24, 5, 31, 14),
(25, 4.9, 31, 17),
(26, 4.5, 33, 19);

-- --------------------------------------------------------

--
-- Table structure for table `thumbs`
--

CREATE TABLE `thumbs` (
  `thumbs_id` int(11) UNSIGNED NOT NULL,
  `user_id` int(11) UNSIGNED NOT NULL,
  `comment_id` int(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `thumbs`
--

INSERT INTO `thumbs` (`thumbs_id`, `user_id`, `comment_id`) VALUES
(11, 21, 8),
(12, 23, 8),
(14, 23, 14),
(15, 23, 17),
(16, 23, 15),
(17, 23, 21),
(18, 23, 18),
(19, 23, 13),
(20, 23, 11),
(21, 23, 20),
(22, 21, 19),
(23, 32, 8),
(24, 32, 24),
(25, 32, 29),
(26, 32, 11),
(27, 32, 30),
(28, 32, 20),
(29, 32, 14),
(30, 32, 17),
(31, 32, 27),
(32, 32, 33),
(33, 32, 36);

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `user_id` int(11) UNSIGNED NOT NULL,
  `name` varchar(100) NOT NULL,
  `contact_no` varchar(15) NOT NULL,
  `Birthday` date NOT NULL,
  `username` varchar(50) NOT NULL,
  `password` char(64) NOT NULL,
  `usertype` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`user_id`, `name`, `contact_no`, `Birthday`, `username`, `password`, `usertype`) VALUES
(1, 'Khairul Amirin', '0166274367', '2003-07-27', 'KHAIRUL123', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Reviewer'),
(2, 'Khairul Amirin', '0166274367', '2003-07-27', 'KHAIRUL234', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Admin'),
(18, 'Khairul Amirin', '0166274367', '2003-07-27', 'KHAIRUL567', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Director'),
(19, 'Khairul Amirin', '0166274367', '2003-07-27', 'KHAIRUL890', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Director'),
(20, 'John Dalton', '0166274367', '2003-07-27', 'JohnDalton23', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Reviewer'),
(21, 'Khairul Amirin', '0166274367', '2003-07-27', 'KHAIRUL000', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Guest'),
(22, 'Riri Suguha', '0166274367', '2003-07-27', 'RiriCute12', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Reviewer'),
(23, 'Khairul Issei', '0166274367', '2003-07-27', 'KHAIRUL222', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Guest'),
(24, 'Ander West', '0166274367', '2003-07-27', 'AnderWest12', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Director'),
(25, 'William Smith', '0166274367', '2003-07-27', 'WilliamSmith12', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Director'),
(26, 'Aina Batrisya', '0166274367', '2003-07-27', 'Aina23', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Guest'),
(27, 'Suhana Aidilah', '0166274367', '2003-07-27', 'Suhaaa12', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Guest'),
(29, 'William Spielberg', '0165456757', '1975-12-24', 'WilliamSpielberg12', 'a22039a8ed020b04fae720e33144b46285a83efa4a57ceb94153fedca68634fc', 'Director'),
(30, 'Christopher Nolan', '01234567029', '1985-03-23', 'Nolan12', '7ed5c6756734da63627fb8ff1a1617e98b8f580c0e1187d1d97dee913a9ed0ab', 'Director'),
(31, 'Amir Masdi', '013455566566', '1983-12-11', 'AmirMasdi12', 'ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f', 'Reviewer'),
(32, 'Ashton Welson', '0977765565', '1975-12-04', 'Ashton12', '9bf86e576cbec37f9ded6cd3fa3ef283f2f2ae6ec59ca468cc9272cb3060a058', 'Guest'),
(33, 'Alan Walker', '0113445564', '1995-05-27', 'Alan12', '8fe0176b3513fa42fa9d7396942f3b4af88ae43af0f35453729e931fe89c6232', 'Reviewer'),
(34, 'Syamsul Yusof', '016274367', '1990-02-24', 'Syamsul12', '3762e41fa5e46fa877ae71bb27c07b1a06534b53723cc9e541750abfb46f8524', 'Director');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `comment`
--
ALTER TABLE `comment`
  ADD PRIMARY KEY (`comment_id`),
  ADD KEY `movie_id` (`movie_id`),
  ADD KEY `user_id` (`user_id`);

--
-- Indexes for table `favorites`
--
ALTER TABLE `favorites`
  ADD PRIMARY KEY (`favorite_id`),
  ADD UNIQUE KEY `unique_user_movie` (`user_id`,`movie_id`),
  ADD KEY `fk_favorite_movie_id` (`movie_id`);

--
-- Indexes for table `movie`
--
ALTER TABLE `movie`
  ADD PRIMARY KEY (`movie_id`),
  ADD KEY `fk_movie_user_id` (`user_id`);

--
-- Indexes for table `rating`
--
ALTER TABLE `rating`
  ADD PRIMARY KEY (`rating_id`),
  ADD KEY `fk_movie_id` (`movie_id`),
  ADD KEY `fk_user_id` (`user_id`);

--
-- Indexes for table `thumbs`
--
ALTER TABLE `thumbs`
  ADD PRIMARY KEY (`thumbs_id`),
  ADD KEY `fk_thumbs_user_id` (`user_id`),
  ADD KEY `fk_thumbs_comment_id` (`comment_id`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`user_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `comment`
--
ALTER TABLE `comment`
  MODIFY `comment_id` int(50) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=37;

--
-- AUTO_INCREMENT for table `favorites`
--
ALTER TABLE `favorites`
  MODIFY `favorite_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=32;

--
-- AUTO_INCREMENT for table `movie`
--
ALTER TABLE `movie`
  MODIFY `movie_id` int(50) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;

--
-- AUTO_INCREMENT for table `rating`
--
ALTER TABLE `rating`
  MODIFY `rating_id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;

--
-- AUTO_INCREMENT for table `thumbs`
--
ALTER TABLE `thumbs`
  MODIFY `thumbs_id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=34;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `user_id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=35;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `comment`
--
ALTER TABLE `comment`
  ADD CONSTRAINT `movie_id` FOREIGN KEY (`movie_id`) REFERENCES `movie` (`movie_id`),
  ADD CONSTRAINT `user_id` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`);

--
-- Constraints for table `favorites`
--
ALTER TABLE `favorites`
  ADD CONSTRAINT `fk_favorite_movie_id` FOREIGN KEY (`movie_id`) REFERENCES `movie` (`movie_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_favorite_user_id` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `movie`
--
ALTER TABLE `movie`
  ADD CONSTRAINT `fk_movie_user_id` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE CASCADE;

--
-- Constraints for table `rating`
--
ALTER TABLE `rating`
  ADD CONSTRAINT `fk_movie_id` FOREIGN KEY (`movie_id`) REFERENCES `movie` (`movie_id`) ON DELETE CASCADE,
  ADD CONSTRAINT `fk_user_id` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE CASCADE;

--
-- Constraints for table `thumbs`
--
ALTER TABLE `thumbs`
  ADD CONSTRAINT `fk_thumbs_comment_id` FOREIGN KEY (`comment_id`) REFERENCES `comment` (`comment_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_thumbs_user_id` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
