#ifndef MYSERIAL_H_
#define MYSERIAL_H_

#include <stddef.h>
#include <windows.h>
#include <commctrl.h>

#define COMPORT "COM2"
HANDLE comPort;

static CHAR * getLastErrorText(CHAR *pBuf, ULONG bufSize);
BOOL initSerial(CHAR *serialPort);

#endif /* MYSERIAL_H_ */
