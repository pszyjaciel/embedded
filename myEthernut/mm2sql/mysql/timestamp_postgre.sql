-- http://www.postgresql.org/docs/9.4/static/functions-sequence.html
-- DROP SEQUENCE timestamp_seq;
CREATE SEQUENCE timestamp_seq START 1 INCREMENT 1;

-- DROP TABLE TimeStampTable;
CREATE TABLE TimeStampTable
(
   idTimeStamp   integer PRIMARY KEY DEFAULT nextval ('timestamp_seq'),
   myTimeStamp   timestamp
);

INSERT INTO TimeStampTable (myTimeStamp)
     VALUES (current_timestamp);

SELECT * FROM TimeStampTable;

-------------- dotad ok. ------------





CREATE OR REPLACE FUNCTION timestamp_autonumber_func ()
   RETURNS TRIGGER
AS
$$
BEGIN
   NEW.idTimeStamp := nextval ('timestamp_seq');
   RETURN NEW;
END;
$$
   LANGUAGE plpgsql;


CREATE TRIGGER timestamp_autonumber_trig
   BEFORE INSERT
   ON myTimeStamp
   FOR EACH ROW
EXECUTE PROCEDURE timestamp_autonumber_func ();



INSERT INTO myTimeStamp
        VALUES (1, '00:00:00', '2015-01-03'),
               (2, '00:00:01', '2015-02-03'),
               (3, '00:00:02', '2015-03-03');

-- http://www.postgresql.org/docs/current/static/functions-srf.html

SELECT generate_series ('2011-02-02 00:00:00'::timestamp,
                        '2012-04-01 05:00:00'::timestamp,
                        '1 hour'::interval)
          AS myStamp;

-- ten myStamp to nazwa kolumny

SELECT generate_series (1::int, 10::int) AS mojOrder;

-- ten myStamp to nazwa kolumny

SELECT current_timestamp;

SELECT CURRENT_TIME;

SELECT CURRENT_DATE;

INSERT INTO myTimeStamp
     VALUES (4, CURRENT_DATE);


CREATE OR REPLACE FUNCTION foo ()
   RETURNS SETOF text
AS
$BODY$
DECLARE
   a     text;
   b     text;
   arr   text [];
   i     INTEGER := 0;
BEGIN
   a = 'a';
   b = 'b';
   arr[0] = a;
   arr[1] = b;

   FOR i IN 0 .. array_upper (arr, 1)
   LOOP
        RETURN NEXT arr[i];
   END LOOP;
END;
$BODY$
   LANGUAGE 'plpgsql'
   VOLATILE;


SELECT * FROM foo ();

SELECT xmlcomment ('hello');

SELECT xmlelement (NAME foo);

CREATE TABLE test
(
   a   xml,
   b   xml
);

SELECT xmlelement (NAME test, xmlattributes (a, b)) FROM test;