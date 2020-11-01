
// ---------------------- smietnik -----------------------

	// read one parameter
//	uint16_t myParam = 0x5e;
//	uint16_t value = getValue(myParam);
//	printf("myParam: %02x, value: %04x \n", myParam, value);
//	printf("myParam: %d, value: %d \n", myParam, value);




	//	PKW Parameter identifier Value
//	PZD Process data
//	PKE Parameter identifier
//	IND Index
//	PWE Parameter Value
//	STW Control word
//	ZSW Status word

//	10 pke, ind		// 1: Request parameter value
//	5d ind			// 93: Timeout (seconds)
//	2d				// 0x2d (45): wartosc parametru

//	zsw				// (str. 11)
	//	13				// 0001 0011
	// Drive ready: yes,
	// Drive ready to run: yes,
	// Drive running: no,
	// Drive fault active: 0 (yes),
	// OFF2 active: 1 (no)

	//	7a				// 0111 1010
	// Deviation setpoint / actual value: yes,
	// PZD control: yes,
	// Maximum frequency reached: no,
	// Warning: Motor current limit: no,
	// Motor holding brake active: no,
	// Motor overload: no,
	// Motor running direction right: yes,
	// Inverter overload: yes





/*rc = WriteFile(m_hCommPort, &init, (DWORD) sizeof(init), &dwBytesWritten,
 NULL);
 if (rc == 0) {
 printf("\nWriteFile(): ");
 printf(getLastErrorText(msgTextBuf, sizeof(msgTextBuf)));
 }

 rc = WriteFile(m_hCommPort, &output, (DWORD) sizeof(output),
 &dwBytesWritten, NULL);

 rc = ReadFile(m_hCommPort, msgTextBuf, 12, &bytesRead, NULL);
 printf("msgTextBuf: %02x \n", msgTextBuf[0]);
 printf("msgTextBuf: %02x \n", msgTextBuf[1]);
 printf("msgTextBuf: %02x \n", msgTextBuf[2]);
 printf("msgTextBuf: %02x \n", msgTextBuf[3]);

 printf("\n\n read: %p: %ld, rc: %d \n", &bytesRead, bytesRead, rc);
 */

//	accum = (stop.tv_sec - start.tv_sec)
//			+ (stop.tv_nsec - start.tv_nsec) / 1000000;
/*	unsigned char mychar;
 unsigned char nibHi;
 unsigned char nibLo;
 unsigned char j;
 static char myTelegram[100];
 const char *ds;

 ds = createStr(myTelegram, '$');
 printf("%s", ds);

 nibHi = (output[0] & 0xf0) >> 4;
 mychar = hex2asc(nibHi);
 ds = createStr(myTelegram, mychar);
 printf("%s \n", ds);

 for (j = 0; j < sizeof(output); j++) {
 nibHi = (output[j] & 0xf0) >> 4;
 mychar = hex2asc(nibHi);
 printf("$%02x", mychar);

 nibLo = output[j] & 0x0f;
 mychar = hex2asc(nibLo);
 printf("$%02x", mychar);

 }
 printf("\n");

 ds = dawajStringa(10);
 printf("%s \n", ds);

 ds = createStr(myTelegram, 0x38);
 printf("%s \n", ds);*/

//	GetCommState(m_hCommPort, &config);
//	printf("config.BaudRate: %d \n ", config.BaudRate);
//	printf("config.ByteSize: %d \n ", config.ByteSize);
//	printf("config.Parity: %d \n ", config.Parity);
/*
 struct timespec start, stop;
 double accum;
 if (clock_gettime( CLOCK_REALTIME, &start) == -1) {
 perror("clock gettime");
 exit( EXIT_FAILURE);
 }
 */

/*
 perror("testing..");
 if (clock_gettime( CLOCK_REALTIME, &stop) == -1) {
 perror("clock gettime");
 exit( EXIT_FAILURE);
 }
 accum = (stop.tv_nsec - start.tv_nsec) / 1000000;	// [milisec]
 printf("\nworking time: %lf\n", accum);
 */

/*
 char* createStr(char* myString, char myValue) {

 myString[0] = myValue;
 myString[1] = 0x00;

 return myString;
 }

 const char* dawajStringa(int month) {
 char *myString = "my string \0";
 return myString;
 }

 unsigned char hex2asc(unsigned char myascii) {

 // mam 0x0c a chce otrzymac 0x30 i 0x..

 if ((myascii >= 0) && (myascii <= 9)) {
 myascii += 0x30;
 } else if ((myascii >= 10) && (myascii <= 15)) {
 // } else {
 myascii += 0x37;
 }

 return myascii;

 }

 //   return error message
 static CHAR * getLastErrorText(CHAR *pBuf, ULONG bufSize) {
 DWORD retSize;
 LPTSTR pTemp = NULL;

 if (bufSize < 16) {
 if (bufSize > 0) {
 pBuf[0] = '\0';
 }
 return (pBuf);
 }

 retSize = FormatMessage(
 FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
 NULL, GetLastError(), LANG_NEUTRAL, (LPTSTR) &pTemp, 0, NULL);
 if (!retSize || pTemp == NULL) {
 pBuf[0] = '\0';
 } else {
 pTemp[strlen(pTemp) - 2] = '\0';   //remove cr and newline character
 sprintf(pBuf, "%0.*s (0x%x)", (int) bufSize - 16, pTemp, (int) GetLastError());
 LocalFree((HLOCAL) pTemp); // Frees the specified local memory object and invalidates its handle.
 }
 return (pBuf);
 }
 */




//	printf("%04x \n", AK << 12);
//	printf("%04x \n", SP << 11);
//	printf("%04x \n", PNU);

//  telegram: 2 * 7 * 2bytes = 28bytes (0x1c)
//  lge pomniejszony o 2
//  STX i LGE sie nie licza

//	021A 0500 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0018

// 50.000 dollar/year

//pkeLO = pke & 0x00ff;
//	printf("%02x, \n", pkeLO);
//
//	pkeHI = (pke & 0xff00) >> 8;
//	printf("%02x, \n", pkeHI);
//
//	pke = 0 | PNU | (AK << 12) | (SP << 11);
//	printf("%04x, \n", pke);

//printf("%04x \n", ((PNUex << 12) & 0xff00) >> 8);     // HI
//printf("%04x \n", IDX & 0x00ff);

//uint8_t i, command;
//command = 4;

//	for (i = 0; i < sizeof(teleArrPtr[command]); i++) {
//		printf("%02x ", teleArrPtr[command][i]);
//	}

//	uint8_t stx = teleArrPtr[command][0];
//	printf("\nstx: %02x \n", stx);

//	1. word
//	uint8_t taskID = (teleArrPtr[command][3] & 0xf0) >> 4;     // 1: Request parameter value
//	printf("taskID: %02x : %d \n", taskID, taskID);
//
//	uint16_t pnu = ((teleArrPtr[command][3] & 0x07) << 8) | teleArrPtr[command][4];		// numer parametru
//	printf("pnu: %04x : %d \n", pnu, pnu);

// 	2. word - nie interesuje (na razie)
//	uint16_t pwe1 = (teleArrPtr[command][5] << 8) | teleArrPtr[command][6];
//	printf("pwe1: %04x : %d \n", pwe1, pwe1);

// 	3. word - wartosc parametru
//	uint16_t pwe2 = (teleArrPtr[command][7] << 8) | teleArrPtr[command][8];
//	printf("pwe2: %04x : %d \n", pwe2, pwe2);

// 	zsw (when reading) or stw (when writting)
//	uint16_t zsw = (teleArrPtr[command][9] << 8) | teleArrPtr[command][10];
//	printf("zsw: %04x : %d \n", zsw, zsw);

//	hiw (when reading) or hsw (when writting)
//	uint16_t hiw = (teleArrPtr[command][11] << 8) | teleArrPtr[command][12];
//	printf("hiw: %04x : %d \n", hiw, hiw);

/*
 1st word: PKE Parameter_ID
 2nd word: IND Index
 3th word: PWE1 Parameter value 1 or High word
 4th word: PWE2 Low word
 */
// Parameter-Kennung-Wert
//typedef struct myPKW {
//	uint8_t pkeLo;    	// ParameterKEnnung
//	uint8_t pkeHi;    	// ParameterKEnnung
//
//	uint8_t indLo;    	// INDex
//	uint8_t indHi;    	// INDex
//
//	uint8_t pwe1Lo;		// 1. ParameterWErt
//	uint8_t pwe1Hi;		// 1. ParameterWErt
//	uint8_t pwe2Lo;		// 1. ParameterWErt
//	uint8_t pwe2Hi;		// 2. ParameterWErt
//
//} myPKW_t;
//
//// ProZessDaten
//typedef struct myPZD1 {
//	uint8_t stw1Hi;
//	uint8_t stw1Lo;
//
////	uint8_t zsw1;
//
//} myPZD1_t;
//
//typedef struct myPZD2 {
//	uint8_t hsw1Hi;
//	uint8_t hsw1Lo;
//
////	uint8_t hiwHi;
////	uint8_t hiwLo;
//
//} myPZD2_t;
//
//typedef struct myPZD3 {
//	uint8_t notLinkedLo;
//	uint8_t notLinkedHi;
//
//} myPZD3_t;
//
//typedef struct myPZD4 {
//	uint8_t stw2;
//	uint8_t zsw2;
//
//} myPZD4_t;
//
//typedef struct myPZD5 {
//	uint8_t notLinkedLo;
//	uint8_t notLinkedHi;
//
//} myPZD5_t;
//
//typedef struct myPZD6 {
//	uint8_t notLinkedLo;
//	uint8_t notLinkedHi;
//
//} myPZD6_t;
//
//typedef struct myPZD7 {
//	uint8_t r31Lo;
//	uint8_t r31Hi;
//
//} myPZD7_t;
//
//typedef struct myPZD8 {
//	uint8_t r32Lo;
//	uint8_t r32Hi;
//
//} myPZD8_t;
//
//typedef struct myTelegramStruct {
//	uint8_t stx;     // always 0x02
//	uint8_t lge;     // max 0xff
//	uint8_t adr;     // adr: 0x1f (bit7 + bit6 + bit5: special meaning)
//	myPKW_t myPKW;		// PKW area of max. 126 words
//	myPZD1_t myPZD1;
//	myPZD2_t myPZD2;
//	myPZD3_t myPZD3;
//	myPZD4_t myPZD4;
//	myPZD5_t myPZD5;
//	myPZD6_t myPZD6;
//	myPZD7_t myPZD7;
//	myPZD8_t myPZD8;
//	uint8_t bcc;     // control sum
//} myTelegramStruct_t;
//
//myTelegramStruct_t myTelegramStruct;


// uint8_t myArray[14] = { 0x02, 0x0C, 0x00, 0x10, 0x5F, 0x00, 0x00, 0x00, 0x01, 0x0B, 0x72, 0x00, 0x00, 0x00 };
//	uint8_t myArray[14] = { 0x02, 0x0C, 0x00, 0x10, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9 };

//	for (i = 0; i < 14; i++) {
//		myTelegram[i] = myArray[i];
//	}
//
//	uint8_t result = calcBCC();
//	myTelegram[13] = calcBCC();
//
//	printf("result: %02x \n", result);
//	printf("myTelegram[13]: %02x \n", myTelegram[13]);


	//	0x02, 0x0c, 0x00, 0x10, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9 }, };
	// cos nie tak z suma kontrolna..
