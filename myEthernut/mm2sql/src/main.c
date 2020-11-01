#include <time.h>
#include "pksql.h"
#include "mySerial.h"

#define MY_GLOBAL_INCLUDED

/**
 * @brief In the main function the connection to mySQL is created, the serial port is being initialized.
 * The data will be readed from serial port until a key was pressed. \n Every message will be parsed into array,
 * which will be used for creating of a SQL-statement. The SQL-command is gonna be executed. \n Finally the serial port
 * and the SQL-connection is getting closed.
 */
int main(int argc, CHAR* argv[]) {
	BOOL rc;
	CHAR msgTextBuf[1024];
	DWORD bytesRead;        		  // NumberOfBytesRead
	DWORD start, end, result;
	int i, j;

	DWORD dwRead;
	BOOL fWaitingOnRead = FALSE;
	OVERLAPPED osReader = {0};

	char mce_table[] = "values_realtime";
	short *shortMsg;

	rc = MySQLConnect();			// connect to mySQL
	if (rc == FALSE) {
		printf("Error with MySQLConnect(). Program exits. \n");
		return -1;
	}

	rc = initSerial(COMPORT);          // If the function succeeds, the return value is nonzero.
	if (rc == FALSE) {
		printf("Error while initSerial(). Program exits. \n");
		return -1;
	}


	cleanBuffer(msgTextBuf);

	while (TRUE) {
		// reads data on port and store it on mySQL server. If succeeds rc is TRUE.
		rc = ReadFile(comPort, msgTextBuf, sizeof(msgTextBuf), &bytesRead, NULL);
		if (rc != FALSE && bytesRead != 0) {
			// parseMessage(msgTextBuf);
			shortMsg = parseMsgToShort(msgTextBuf, bytesRead);
			rc = updateMMData(mce_table, shortMsg);
			// rc = insertMMData(mce_table, shortMsg);
			if (rc == FALSE) {
				printf("Error while insertSQLData(). Program will continue. \n");
			} else {
				printf("MM-data successfull updated. \n");
			}
			// printf("%s \n", msgTextBuf);
		}
	}

	rc = CloseHandle(comPort);        	// If succeeds, rc is TRUE.
	if (rc == FALSE) {
		printf("Error while CloseHandle(). Program exits. \n");
		return -1;
	}

	mysql_close(g_pMySQL);
	mysql_library_end();

	printf("\n\nEnd of program..");
	return 0;
}
