create database maintenance;

CREATE TABLE TimeStampTable
(
   idTimeStamp   integer AUTO_INCREMENT,
   myTimeStamp   timestamp,
   PRIMARY KEY (idTimeStamp)
);

INSERT INTO TimeStampTable (myTimeStamp)
     VALUES (current_timestamp);

SELECT * FROM TimeStampTable;

----------
DROP TABLE values_realtime;

CREATE TABLE values_realtime
(
   id integer AUTO_INCREMENT,
   machine varchar(15),
   r131 integer(4),
   r132 integer(3),
   r133 integer(3),
   r134 integer(4),
   r135	integer(4),
   TStamp timestamp,
   PRIMARY KEY (id)
);


INSERT INTO values_realtime (machine, r131, r132, r133, r134, r135, tstamp)
     VALUES ('siemens', 1, 0, 1, 1, 0, current_timestamp);

DELETE FROM values_realtime WHERE id =3;

CREATE TABLE values_realtime
(
   machine varchar(15),
   r131 integer(4),
   r132 integer(3),
   r133 integer(3),
   r134 integer(4),
   r135	integer(4),
   TStamp timestamp,
   PRIMARY KEY (machine)
);