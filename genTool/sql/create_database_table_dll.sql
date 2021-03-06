CREATE DATABASE IF NOT EXISTS imsixthr_myweb02 character set utf8;
CREATE USER 'imsixthr_myweb'@'localhost' IDENTIFIED BY 'imsixthr_myweb';
GRANT ALL ON imsixthr_myweb02.* TO 'myweb'@'localhost';
GRANT ALL ON imsixthr_myweb02.* TO 'imsixthr_myweb'@'localhost';
use imsixthr_myweb02;

-- this table has a mapping between list ids and song ids 
CREATE TABLE `d_id_map` (
 `list_id` int(11) NOT NULL,
 `music_id` bigint(20) NOT NULL,
 `insert_ts` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
 KEY `music_id_idx` (`music_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

-- the topic types in my website
CREATE TABLE `d_topic_type` (
 `topic_type_id` tinyint(4) NOT NULL AUTO_INCREMENT,
 `topic_type_desc` varchar(100) NOT NULL,
 `modified_ts` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
 PRIMARY KEY (`topic_type_id`),
 KEY `modified_ts` (`modified_ts`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

-- poem and quotations
CREATE TABLE `f_poem` (
 `poem_id` int(11) NOT NULL AUTO_INCREMENT,
 `poem_content` varchar(4000) NOT NULL,
 `poet` varchar(100) DEFAULT NULL,
 `modified_ts` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
 PRIMARY KEY (`poem_id`),
 KEY `modified_ts` (`modified_ts`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

-- The detailed song info, such as artist, album, lyrics
CREATE TABLE `f_song_info` (
  `song_id` bigint(20) NOT NULL,
  `title` varchar(500) DEFAULT NULL,
  `artist` varchar(500) DEFAULT NULL,
  `album` varchar(500) DEFAULT NULL,
  `lyric` text,
  `insert_ts` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

-- The topics
CREATE TABLE `f_topic` (
  `topic_id` int(11) NOT NULL AUTO_INCREMENT,
  `topic_type_id` tinyint(4) NOT NULL,
  `topic_name` varchar(100) NOT NULL,
  `topic_tags` varchar(4000) DEFAULT NULL,
  `topic_recom_flag` varchar(4000) DEFAULT 'N',
  `modified_ts` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`topic_id`),
  KEY `modified_ts` (`modified_ts`),
  KEY `topic_recom_flag` (`topic_recom_flag`(255)),
  KEY `topic_type_id` (`topic_type_id`),
  CONSTRAINT `f_topic_ibfk_1` FOREIGN KEY (`topic_type_id`) REFERENCES `d_topic_type` (`topic_type_id`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

-- list info of a topic
CREATE TABLE `f_topic_list` (
  `list_id` int(11) NOT NULL AUTO_INCREMENT,
  `topic_id` int(11) NOT NULL,
  `list_name` varchar(100) NOT NULL,
  `list_desc` text,
  `list_image_loc` varchar(4000) DEFAULT NULL,
  `list_outer_link` varchar(4000) DEFAULT NULL,
  `list_other_link` varchar(4000) DEFAULT NULL,
  `modified_ts` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`list_id`),
  KEY `modified_ts` (`modified_ts`),
  KEY `topic_id` (`topic_id`),
  CONSTRAINT `f_topic_list_ibfk_1` FOREIGN KEY (`topic_id`) REFERENCES `f_topic` (`topic_id`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

-- stage tables
CREATE TABLE `stg_d_id_map_w` (
  `list_id` int(11) NOT NULL,
  `music_id` bigint(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

CREATE TABLE `stg_f_song_info_w` (
  `song_id` bigint(20) NOT NULL,
  `title` varchar(500) DEFAULT NULL,
  `artist` varchar(500) DEFAULT NULL,
  `album` varchar(500) DEFAULT NULL,
  `lyric` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

CREATE TABLE `stg_f_topic_list_w` (
  `list_id` int(11) NOT NULL,
  `topic_id` int(11) NOT NULL,
  `list_name` varchar(100) NOT NULL,
  `list_desc` text,
  `list_image_loc` varchar(4000) DEFAULT NULL,
  `list_outer_link` varchar(4000) DEFAULT NULL,
  `list_other_link` varchar(4000) DEFAULT NULL,
  `modified_ts` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`list_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;


CREATE TABLE `stg_f_topic_w` (
  `topic_id` int(11) NOT NULL,
  `topic_type_id` tinyint(4) NOT NULL,
  `topic_name` varchar(100) NOT NULL,
  `topic_tags` varchar(4000) DEFAULT NULL,
  `topic_recom_flag` varchar(4000) DEFAULT NULL,
  `modified_ts` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`topic_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 
;




