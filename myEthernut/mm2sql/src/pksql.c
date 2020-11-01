#include "pksql.h"

unsigned short char2short(unsigned char *val)
{
	unsigned short temp;
	unsigned short myTemp;

	myTemp = (*(val + 0));
	if (myTemp > 0x40)
		myTemp -= 0x37;          // convert chars a-f
	else
		myTemp -= 0x30;          // convert chars 0-9
	temp = myTemp * 0x1000;

	myTemp = (*(val + 1));
	if (*(val + 1) > 0x40)
		myTemp -= 0x37;          // convert chars a-f
	else
		myTemp -= 0x30;          // convert chars 0-9
	myTemp = myTemp * 0x0100;
	temp = temp + myTemp;

	myTemp = (*(val + 2));
	if (*(val + 2) > 0x40)
		myTemp -= 0x37;          // convert chars a-f
	else
		myTemp -= 0x30;          // convert chars 0-9
	myTemp = myTemp * 0x0010;
	temp = temp + myTemp;

	myTemp = (*(val + 3));
	if (*(val + 3) > 0x40)
		myTemp -= 0x37;          // convert chars a-f
	else
		myTemp -= 0x30;          // convert chars 0-9
	temp = temp + myTemp;

	return temp;
}

static char * short2String(short int n)
{
	static char myStr[7];
	unsigned char d4, d3, d2, d1, d0, q;
	int i;

	if (n < 0)
	{
		myStr[0] = '-';
		n = -n;
	}
	else
	{
		myStr[0] = '+';
	}
	d1 = (n >> 4) & 0x0F;
	d2 = (n >> 8) & 0x0F;
	d3 = (n >> 12) & 0x0F;

	d0 = 6 * (d3 + d2 + d1) + (n & 0x0F);
	q = (d0 * 0xCD) >> 11;
	d0 = d0 - 10 * q;

	d1 = q + 9 * d3 + 5 * d2 + d1;
	q = (d1 * 0xCD) >> 11;
	d1 = d1 - 10 * q;

	d2 = q + 2 * d2;
	q = (d2 * 0x1A) >> 8;
	d2 = d2 - 10 * q;

	d3 = q + 4 * d3;
	d4 = (d3 * 0x1A) >> 8;
	d3 = d3 - 10 * d4;
	myStr[1] = d4 + '0';
	myStr[2] = d3 + '0';
	myStr[3] = d2 + '0';
	myStr[4] = d1 + '0';
	myStr[5] = d0 + '0';
	i = 5;
	// === remove the left zero =========
	while (myStr[1] == '0' && i > 1)
	{
		int j;
		for (j = 1; j < i; j++)
		{
			myStr[j] = myStr[j + 1];
		}
		i--;
	}
	myStr[i + 1] = '\0';
	return myStr;
}

void cleanBuffer(char *buffer2clean)
{
	int i;
	int lbuf = sizeof(buffer2clean);
	for (i = 0; i < lbuf; i++)
	{
		buffer2clean[i] = 0;
	}
}

BOOL displayAllFromTable(char *myTable, int myID)
{
	char *idStr;
	char szBuf[256];
	char szSQL[512];
	MYSQL_RES *pRes;
	MYSQL_ROW row;

	strcpy(szSQL, "SELECT count(*) FROM ");
	strcat(szSQL, myTable);

	/* Now, issue the query. */
	if (mysql_query(g_pMySQL, szSQL) != 0)
	{
		printf("Error in mysql_query(): %s \n", mysql_error(g_pMySQL));
		return FALSE;
	}

	/* Get the resultset. */
	row = mysql_fetch_row(mysql_store_result(g_pMySQL));
	printf("SELECT count(*) FROM sensors: %s \n", row[0]);

	// ----------------------------------

	/* Build SQL statement. */
	idStr = _itoa(myID, szBuf, 10);

	strcpy(szSQL, "SELECT * FROM ");
	strcat(szSQL, myTable);
	strcat(szSQL, " WHERE id = ");
	strcat(szSQL, szBuf);
	strcat(szSQL, "\0");

	printf("\n%s\n", szSQL);

	/* Now, issue the query. */
	if (mysql_query(g_pMySQL, szSQL) != 0)
	{
		printf("Error in mysql_query(): %s \n", mysql_error(g_pMySQL));
		return FALSE;
	}

	/* Get the resultset. */
	if ((pRes = mysql_store_result(g_pMySQL)) == NULL)
	{
		printf("Error in mysql_store_result(): %s \n", mysql_error(g_pMySQL));
		return FALSE;
	}

	/* Loop for all rows found. */
	if ((row = mysql_fetch_row(pRes)) != NULL)
	{
		printf("id: %s \n", row[0]);
		printf("machine_id: %s \n", row[1]);
		printf("sensor_id: %s \n", row[2]);
		printf("state: %s \n", row[3]);
		printf("timestamp: %s \n", row[4]);
	}

	/* Free MySQL Resultset. */
	mysql_free_result(pRes);

	return TRUE;
}

short * parseMsgToShort(char *msgTextBuf, DWORD msgLength)
{
	unsigned char mySign, j;
	short myWord;
	unsigned char counter = 0;
	unsigned char index = 0;
	unsigned char myCharArray[4];
	static unsigned short mmValShort[128];
	short i;

	// check if mmValShort is large enough, if too small then mmValShort must be expanded
	// printf("msgLength: %d \n ", msgLength);

	// here we parse the string
	while (*msgTextBuf != 0)
	{
		mySign = *msgTextBuf;
		if ((mySign != 0x20) && (mySign != 0x3a) && (mySign != 0x0d) && (mySign != 0x0a))
		{
			myCharArray[counter] = mySign;
			counter++;

			if (counter == 4)       				 // must jump in for each 4th time
			{
				myWord = char2short(myCharArray);
				mmValShort[index] = myWord;
				index++;
				counter = 0;
			}
		}
		msgTextBuf++;
	}          // end of 'while'
	return mmValShort;
}

BOOL insertMMData(char *myTable, short myShortMsg[])
{
	char szSQL[512];

	//		INSERT INTO values_realtime (machine, r131, r132, r133, r134, r135, tstamp)
	//	    VALUES ('siemens', 1, 0, 1, 1, 0, current_timestamp);

	strcpy(szSQL, "INSERT INTO ");
	strcat(szSQL, myTable);
	strcat(szSQL, " (machine, r131, r132, r133, r134, r135, tstamp) VALUES ('");
	strcat(szSQL, short2String(myShortMsg[1]));
	strcat(szSQL, "', ");
	strcat(szSQL, short2String(myShortMsg[5]));
	strcat(szSQL, ", ");
	strcat(szSQL, short2String(myShortMsg[7]));
	strcat(szSQL, ", ");
	strcat(szSQL, short2String(myShortMsg[9]));
	strcat(szSQL, ", ");
	strcat(szSQL, short2String(myShortMsg[11]));
	strcat(szSQL, ", ");
	strcat(szSQL, short2String(myShortMsg[13]));
	strcat(szSQL, ", current_timestamp);");

	printf("\n%s\n", szSQL);

	/* Now, issue the query. */
	if (mysql_query(g_pMySQL, szSQL) != 0)
	{
		printf("Error in mysql_query(): %s \n", mysql_error(g_pMySQL));
		return FALSE;
	}
	return TRUE;
}

BOOL updateMMData(char *myTable, short myShortMsg[])
{
	char szSQL[512];

	// UPDATE myTable
	// SET r131=value, r132=value2, r133=value2, r134=value2, r135=value2, tstamp=current_timestamp
	// WHERE machine=1
	strcpy(szSQL, "UPDATE ");
	strcat(szSQL, myTable);
	strcat(szSQL, " SET r131=");
	strcat(szSQL, short2String(myShortMsg[5]));
	strcat(szSQL, ", r132=");
	strcat(szSQL, short2String(myShortMsg[7]));
	strcat(szSQL, ", r133=");
	strcat(szSQL, short2String(myShortMsg[9]));
	strcat(szSQL, ", r134=");
	strcat(szSQL, short2String(myShortMsg[11]));
	strcat(szSQL, ", r135=");
	strcat(szSQL, short2String(myShortMsg[13]));
	strcat(szSQL, ", tstamp=current_timestamp WHERE machine=");
	strcat(szSQL, short2String(myShortMsg[1]));
	strcat(szSQL, ";");

	// printf("\n%s\n", szSQL);

	/* Now, issue the query. */
	if (mysql_query(g_pMySQL, szSQL) != 0)
	{
		printf("Error in mysql_query(): %s \n", mysql_error(g_pMySQL));
		return FALSE;
	}
	return TRUE;
}

BOOL insertTimeStamp(char *myTable, char *column)
{
	char szSQL[512];

// INSERT INTO TimeStampTable (myTimeStamp) VALUES (current_timestamp);
	strcpy(szSQL, "INSERT INTO ");
	strcat(szSQL, myTable);
	strcat(szSQL, "(");
	strcat(szSQL, column);
	strcat(szSQL, ") VALUES (current_timestamp)");

	printf("\n%s\n", szSQL);

	/* Now, issue the query. */
	if (mysql_query(g_pMySQL, szSQL) != 0)
	{
		printf("Error in mysql_query(): %s \n", mysql_error(g_pMySQL));
		return FALSE;
	}
	return TRUE;
}

BOOL MySQLConnect()
{
	int g_nMySQLOptions = sizeof(g_pMySQLOptions) / sizeof(char *) - 1;

	/* Initialize MySQL Embedded libmysqld. */
	if (mysql_library_init(g_nMySQLOptions, g_pMySQLOptions, (char **) g_pMySQLOptionGroups) != 0)
	{
		printf("Error initialazing MySQL Embedded \n");
		return FALSE;
	}
	else
	{
		printf("Initialazing MySQL OK. \n");
	}

	/* Initialize MySQL Library. */
	if ((g_pMySQL = mysql_init(NULL)) == NULL)
	{
		mysql_library_end();
		printf("Memory allocation error: %s \n", mysql_error(g_pMySQL));
		return FALSE;
	}
	else
	{
		printf("Memory allocation OK. \n");
	}

	/* Force use of embedded libmysqld. */
	mysql_options(g_pMySQL, MYSQL_OPT_USE_EMBEDDED_CONNECTION, NULL);

	/* Connect to MySQL. */
	if (mysql_real_connect(g_pMySQL, LOCALHOST, USER, PASS, DBNAME, 0, NULL, 0) == NULL)
	{
		printf("Error connecting to MySQL: %s \n", mysql_error(g_pMySQL));

		mysql_close(g_pMySQL);
		mysql_library_end();
		return FALSE;
	}
	else
	{
		printf("Connected with MySQL. \n");
	}
	return TRUE;
}          // End of MySQLConnect()

