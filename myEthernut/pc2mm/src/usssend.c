// https://msdn.microsoft.com/en-us/library/ff802693.aspx

#include "usssend.h"

// typedef unsigned char uint8_t;

uint8_t* sendReadTelegram(uint8_t* myTelegram) {

	DCB config =
		{ 0 };
	DWORD dwBytesWritten;
	DWORD bytesRead;          // NumberOfBytesRead
	uint8_t i;
	int rc;
	COMMTIMEOUTS timeouts;

	const char * port = "COM3";
	HANDLE m_hCommPort = CreateFile(port, GENERIC_READ | GENERIC_WRITE,          //access ( read and write)
			0,          //(share) 0:cannot share the COM port
			0,          //security  (None)
			OPEN_EXISTING,          // creation : open_existing
			FILE_FLAG_WRITE_THROUGH,          // we dont want overlapped operation
			0          // no templates file for COM port...
			);

	int gcs = GetCommState(m_hCommPort, &config);
	if (gcs == 0) {
		printf("GetCommState(): %d \n", gcs);
		return FALSE;
	}

	config.DCBlength = sizeof(config);
	config.fBinary = TRUE;
	config.BaudRate = 9600;
	config.StopBits = ONESTOPBIT;
	config.Parity = EVENPARITY;          // even parity!
	config.fParity = TRUE;
	config.ByteSize = DATABITS_8;
	config.fDtrControl = RTS_CONTROL_DISABLE;
	config.fRtsControl = RTS_CONTROL_DISABLE;
	config.fOutxCtsFlow = FALSE;
	config.fOutxDsrFlow = FALSE;
	config.fTXContinueOnXoff = TRUE;

	rc = SetCommState(m_hCommPort, &config);
	if (rc == 0) {
		perror("SetCommState");
	}

	timeouts.ReadIntervalTimeout = 0;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 500;          // gdy 0 to zwiecha, 50 to takie minimum
	timeouts.WriteTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 500;

	rc = SetCommTimeouts(m_hCommPort, &timeouts);          // If the function fails, the return value is zero.
	if (rc == 0) {
		perror("\nSetCommTimeouts(): ");
	}

	rc = WriteFile(m_hCommPort, myTelegram, 14, &dwBytesWritten, NULL);
	if (rc == 0) {
		perror("\nWriteFile(): ");
	}

	// display telegram
	printf("w: ");
	for (i = 0; i < 14; i++) {
		printf("%02x ", myTelegram[i]);
	}
	printf("\n");

	// clean the buffer
	for (i = 0; i < 14; i++) {
		myTelegram[i] = 0xFF;
	}

	rc = ReadFile(m_hCommPort, myTelegram, 14, &bytesRead, NULL);
	if (rc == 0) {
		perror("\nReadFile()");
	}

	// display telegram
	printf("r: ");
	for (i = 0; i < 14; i++) {
		printf("%02x ", myTelegram[i]);
	}
	printf("\n");

	CloseHandle(m_hCommPort);
	return myTelegram;
}
