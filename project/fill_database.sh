#!/bin/bash

sudo mysql -u root <<QUERY

USE test;

INSERT INTO user (login, password)
  VALUES
  ("alice", "alice"),
  ("andrew", "andrew"),
  ("oleg", "oleg"),
  ("antony", "antony");

INSERT INTO song (name, author, genre, duration, date)
  VALUES
  ("Nice Boi", "Eskimo Callboy", "metalcore", 159, "2019-11-01"),
  ("Black Files", "Ben Howard", "indie folk", 381, "2011-09-30"),
  ("Waiting for You", "Nick Cave & The Bad Seeds", "alternative rock", 234, "2019-10-04"),
  ("Hunger", "The Score", "alternative rock", 123, "2019-08-09"),
  ("Sweet Disposition", "The Temper Trap", "indie rock", 234, "2008-01-01"),
  ("Into My Arms", "Nick Cave & The Bad Seeds", "alternative rock", 256, "1997-03-02"),
  ("Prey", "The Neighbourhood", "indie pop", 282, "2015-10-30"),
  ("Mr. Brightside", "The Killers", "alternative rock", 222, "2003-09-29"),
  ("Bright Horses", "Nick Cave & The Bad Seeds", "alternative rock", 292, "2019-10-04"),
  ("The Man", "The Killers", "alternative rock", 248, "2017-09-22"),
  ("Моя душа", "Andro", "pop", 155, "2019-12-19"),
  ("nextstep", "lowlife", "R&B", 148, "2019-12-17"),
  ("Мишка", "Пошлая Молли feat. KATERINA", "pop", 158, "2019-12-19"),
  ("associate", "масло черного тмина", "hip-hop", 126, "2019-12-19"),
  ("Ready To Die", "EARTHGANG", "hip-hop", 198, "2019-09-01"),
  ("Angelic Hoodrat", "Kenny Mason", "rap", 172, "2019-12-17"),
  ("Мое любимое", "Елена Темникова", "pop", 234, "2019-12-19"),
  ("Напомни", "Скриптонит", "hip-hop", 201, "2019-12-24"),
  ("Поворот (ft. Niman)", "Скриптонит", "hip-hop", 244, "2019-12-24"),
  ("Ага, ну", "Скриптонит", "hip-hop", 187, "2019-12-24");


 INSERT INTO like_dislike (user_id, song_id, value)
   VALUES
   (2, 1, false),
   (3, 1, true),
   (4, 1, false),
   (2, 2, true),
   (4, 2, true),
   (1, 3, true),
   (1, 4, true),
   (2, 4, true),
   (4, 4, true),
   (1, 5, true),
   (1, 6, true),
   (2, 7, true),
   (3, 7, true),
   (4, 7, true),
   (3, 8, false);

INSERT INTO listen (user_id, song_id, count)
  VALUES
  (2, 1, 1),
  (3, 1, 6),
  (4, 1, 1),
  (2, 2, 7),
  (4, 2, 5),
  (1, 3, 9),
  (1, 4, 26),
  (2, 4, 28),
  (4, 4, 11),
  (1, 5, 20),
  (1, 6, 30),
  (2, 7, 10),
  (3, 7, 13),
  (4, 7, 3),
  (3, 8, 1);

QUERY
