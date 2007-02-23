-- UtopiaDB - A multimedia database application and library with a clean
-- API and lots of features, including multiple languages per entry.
--
-- Copyright (C) 2006 John Eric Martin <cpuwhiz105@users.sourceforge.net>
--
-- This program is free software; you can redistribute it and/or modify
-- it under the terms of the GNU General Public License version 2 as
-- published by the Free Software Foundation.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program; if not, write to the
-- Free Software Foundation, Inc.,
-- 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

-- CREATE TABLE `test` (`uid` INT UNSIGNED NOT NULL PRIMARY KEY, `id` INT UNSIGNED NOT NULL , `lang` VARCHAR(5) NOT NULL , `title` VARCHAR(255) NOT NULL);
-- INSERT INTO `test` ('uid', `id`, `lang`, `title`) VALUES ('1', '1', 'en', 'Sony Records');
-- INSERT INTO `test` ('uid', `id`, `lang`, `title`) VALUES ('2', '1', 'ja', 'ソニーミュージックレコーズ');
-- SELECT `lang`,`title` FROM `test` WHERE `id` == '1' ORDER BY `title`, `lang` ASC LIMIT 0, 1; // or DESC
-- SELECT `title` FROM `test` WHERE `id` == '1' AND `lang` == 'en' ORDER BY `title` ASC;
-- UPDATE `test` SET `id` = '1' WHERE `uid` = 2;
-- DELETE FROM `test` WHERE 'uid' = '2';
-- DROP TABLE `test`;


-- SELECT `value` FROM `utopiadb` WHERE `key` == 'dbver' LIMIT 1;
-- SELECT `native` FROM `languages` ORDER BY `code` ASC;
-- SELECT `native` FROM `countries` ORDER BY `code` ASC;

-- Create our tables
CREATE TABLE `artists` (`id` INT UNSIGNED NOT NULL PRIMARY KEY, `birthday` VARCHAR(10) ); -- In the form 'YYYY-MM-DD'
CREATE TABLE `artist_names` (`uid` INT UNSIGNED NOT NULL PRIMARY KEY, `id` INT UNSIGNED NOT NULL, `lang` VARCHAR(5), `name` VARCHAR(128) );

CREATE TABLE `albums` (`id` INT UNSIGNED NOT NULL PRIMARY KEY, `artist` INT UNSIGNED NOT NULL, `cover` VARCHAR(1024) );
CREATE TABLE `album_names` (`uid` INT UNSIGNED NOT NULL PRIMARY KEY, `id` INT UNSIGNED NOT NULL, `lang` VARCHAR(5), `name` VARCHAR(128) );

CREATE TABLE `songs` (`id` INT UNSIGNED NOT NULL PRIMARY KEY, `artist` INT UNSIGNED NOT NULL, `cover` VARCHAR(1024) );
CREATE TABLE `song_names` (`uid` INT UNSIGNED NOT NULL PRIMARY KEY, `id` INT UNSIGNED NOT NULL, `lang` VARCHAR(5), `name` VARCHAR(128) );

-- Fill in some basic info
-- INSERT INTO `artists` ('uid', `id`, `lang`, `name`) VALUES ('1', '1', 'en', 'Morning Musume');
-- INSERT INTO `artists` ('uid', `id`, `lang`, `name`) VALUES ('2', '1', 'ja', 'モーニング娘。');
