#include "MyUtils.h"

// volatile: coby nie optymalizowal zmiennej
void TrackSignalByValue(volatile uint8_t myValue) {
	__asm__ __volatile__ ( "push {r1}");
	__asm__ __volatile__ ( "push {r0}");

	switch (myValue) {
	case 0:
		CLEAROSCIBIT0;
		CLEAROSCIBIT1;
		CLEAROSCIBIT2;
		CLEAROSCIBIT3;
		break;
	case 1:
		SETOSCIBIT0;
		CLEAROSCIBIT1;
		CLEAROSCIBIT2;
		CLEAROSCIBIT3;
		break;
	case 2:
		CLEAROSCIBIT0;
		SETOSCIBIT1;
		CLEAROSCIBIT2;
		CLEAROSCIBIT3;
		break;
	case 3:
		SETOSCIBIT0;
		SETOSCIBIT1;
		CLEAROSCIBIT2;
		CLEAROSCIBIT3;
		break;

	case 4:
		CLEAROSCIBIT0;
		CLEAROSCIBIT1;
		SETOSCIBIT2;
		CLEAROSCIBIT3;
		break;

	case 5:
		SETOSCIBIT0;
		CLEAROSCIBIT1;
		SETOSCIBIT2;
		CLEAROSCIBIT3;
		break;

	case 6:
		CLEAROSCIBIT0;
		SETOSCIBIT1;
		SETOSCIBIT2;
		CLEAROSCIBIT3;
		break;

	case 7:
		SETOSCIBIT0;
		SETOSCIBIT1;
		SETOSCIBIT2;
		CLEAROSCIBIT3;
		break;

		// dokonczyc 8-15
	case 8:
		CLEAROSCIBIT0;
		CLEAROSCIBIT1;
		CLEAROSCIBIT2;
		SETOSCIBIT3;
		break;

	case 9:
		SETOSCIBIT0;
		CLEAROSCIBIT1;
		CLEAROSCIBIT2;
		SETOSCIBIT3;
		break;

	case 10:
		CLEAROSCIBIT0;
		SETOSCIBIT1;
		CLEAROSCIBIT2;
		SETOSCIBIT3;
		break;

	case 11:
		SETOSCIBIT0;
		SETOSCIBIT1;
		CLEAROSCIBIT2;
		SETOSCIBIT3;
		break;

	case 12:
		CLEAROSCIBIT0;
		CLEAROSCIBIT1;
		SETOSCIBIT2;
		SETOSCIBIT3;
		break;

	case 13:
		SETOSCIBIT0;
		CLEAROSCIBIT1;
		SETOSCIBIT2;
		SETOSCIBIT3;
		break;

	case 14:
		CLEAROSCIBIT0;
		SETOSCIBIT1;
		SETOSCIBIT2;
		SETOSCIBIT3;
		break;

	case 15:
		SETOSCIBIT0;
		SETOSCIBIT1;
		SETOSCIBIT2;
		SETOSCIBIT3;
		break;

	default:
		CLEAROSCIBIT0;
		CLEAROSCIBIT1;
		CLEAROSCIBIT2;
		CLEAROSCIBIT3;
		break;
	}
	__asm__ __volatile__ ( "pop {r0}");
	__asm__ __volatile__ ( "pop {r1}");
}

