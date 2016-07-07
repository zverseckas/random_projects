CREATE TABLE IF NOT EXISTS `salons` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `title` varchar(250) DEFAULT NULL,
  `address` varchar(500) DEFAULT NULL,
  `description` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

INSERT INTO `salons` (`id`, `title`, `address`, `description`) VALUES
(1, 'Antakalnio šūdkipyklė', 'Antakalnio g. 65a', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. In sagittis, nisl ac hendrerit scelerisque, urna lorem venenatis nisi, eget gravida massa dolor sit amet dolor. Fusce porta venenatis augue, id blandit orci suscipit nec.'),
(2, 'Pašilaičių skutykla', 'Žemynos g. 51d', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. In sagittis, nisl ac hendrerit scelerisque, urna lorem venenatis nisi, eget gravida massa dolor sit amet dolor.'),
(3, 'Pas Onutę Paliokinę', 'S. Stanevičiaus g. 98a-14', 'In sagittis, nisl ac hendrerit scelerisque, urna lorem venenatis nisi, eget gravida massa dolor sit amet dolor. Fusce porta venenatis augue, id blandit orci suscipit nec.Lorem ipsum dolor sit amet, consectetur adipiscing elit. ');