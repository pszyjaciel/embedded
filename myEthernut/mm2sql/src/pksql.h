#ifndef PKSQL_H_
#define PKSQL_H_

#include <stddef.h>
#include "mysql.h"

#define DBNAME "maintenance"
#define LOCALHOST "127.0.0.1"	// mysql doesn't like localhost
#define USER "root"
#define PASS "admin"

char szSQL[1024];
MYSQL *g_pMySQL;

static char *g_pMySQLOptions[] =
{ "MyTimeStamp", "--datadir=./data", "--language=./language", "--skip-innodb", "--key-buffer-size=64M", "--console",
		NULL };

static char *g_pMySQLOptionGroups[] =
{ "MyTimeStamp", NULL };

/**
 * @brief myRegisters[] is a table of registers, which parameters are aquired on serial port
 */
static short myRegisters[6] =
{ 0x01, 0x83, 0x84, 0x85, 0x86, 0x87 };        // machine, r131, r132, r133, r134, r135

/**
 * This function converts an array of 4 chars to a short value
 * @param *val is pointer to the array of 4 chars
 * @return function returns an unsigned short value as hex representation
 */
unsigned short char2short(unsigned char *val);

/**
 * This function converts a short value 'n' to string with sign
 * @param n is a signed value passed to the function
 * @return a pointer to a string array of bytes
 */
static char * short2String(short int n);

/**
 * @brief This function cleans the buffer which will be filled out with data from serial port.
 * @param buffer2clean is the pointer to a string.
 * @return no return.
 */
void cleanBuffer(char *buffer2clean);

/**
 * @brief This function parse an incomming string message into array of short values.
 * @param *msgTextBuf is a pointer to the message string which was readed from serial port
 * @param msgLength is the length of the message string (here: bytes readed from serial port)
 * @return function returns an array of short values.
 */
short * parseMsgToShort(char *msgTextBuf, DWORD msgLength);

/**
 * @brief This function reads and displays all values from a table myTable, in a row defined by myID
 * @param *myTable is a pointer to a table
 * @param myID is a primary key in the table myTable
 * @return TRUE: If everything was ok
 * \n FALSE: If there was an error.
 */
BOOL displayAllFromTable(char *myTable, int myID);

/**
 * @brief This function prepares a SQL-statement and inserts data into the table myTable of mySQL-database.
 * \n The data are register-values aquired from MicroMaster. The register names are located in odd cells of the array.
 * \n The corresponding values are located in even cells of the array. Finally the SQL-statement is executed.
 * @param *myTable is the pointer to the name of table
 * @param myShortMsg[] is an array of values of type \b short which has been read from serial port
 * @return TRUE is success, FALSE if an error occured
 */
BOOL insertMMData(char *myTable, short myShortMsg[]);

/**
 * @brief This function prepares a SQL-statement and replaces data into the table myTable of mySQL-database.
 * \n Like the insertMMData() data to be replaced are register-values aquired from the MicroMaster.
 * \n Finally the SQL-statement is going to be executed.
 * @param *myTable is the pointer to the name of table
 * @param shortMsg[] is an array of values of type \b short which has been read from serial port
 * @return TRUE is success, FALSE if an error occured
 */
BOOL updateMMData(char *myTable, short shortMsg[]);

/**
 * @brief Function inserts into mySQL-Database an actual date and time (called Time Stamp).
 * @param *myTable is a pointer to the name of DB-table
 * @param *column is a pointer to the name of column which collects the time-stamps
 * @return TRUE is success, FALSE if an error occured
 */
BOOL insertTimeStamp(char *myTable, char *column);

/**
 * @brief Function make an attempt to connect to the mySQL database. It calls internally functions from the libmysql.dll
 * @return TRUE: If everything was ok
 * \n FALSE: If there was an error.
 */
BOOL MySQLConnect();

#endif /* PKSQL_H_ */
