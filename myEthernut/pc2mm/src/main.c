/**
 * \mainpage Aquiring content of registers with the USS-protocol
 * \anchor intro_sec
 * VS2010 project. This program displays the content of registers of the MicroMaster inverter on the PC screen.
 * \n Must connect the MicroMaster device to the rs232-rs485 pcb according to the schematic:
 * <a href="../../hardware/schematic-rs232-rs485.pdf">schematic-rs232-rs485.pdf</a>
 * \n The DSUB connector goes to the serial port COM1 of PC.
 */

#include "usscalc.h"
#include "usssend.h"

int main()
{
	// read multiple parameters
	unsigned char i;
	unsigned short myParamArr[11] =
	{ 1, 111, 131, 132, 133, 134, 135, 210, 721, 723, 923 };
	unsigned short myParamArrCopy[sizeof(myParamArr)];          // make a copy

	for (i = 0; i < (sizeof(myParamArr) / 2); i++)
	{
		myParamArrCopy[i] = myParamArr[i];
	}

	getAllValues(myParamArr, sizeof(myParamArr) / 2);

	for (i = 0; i < (sizeof(myParamArr) / 2); i++)
	{
		// printf("[%04x]: %04x \n", myParamArrCopy[i], myParamArr[i]);
		printf("\n[%d]: %d", myParamArrCopy[i], myParamArr[i]);
	}
	return 0;
}

