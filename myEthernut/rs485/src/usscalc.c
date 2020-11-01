
/**
 * @page referenced_documents This Page references to some documents about USS protocol.
 * \section links_sec Links:
 * \n <a href="../../literature/USS2LabVIEW.pdf">USS2LabVIEW.pdf</a>
 * \n <a href="../../literature/Cykliczna i acykliczna komunikacja.pdf">Cykliczna i acykliczna komunikacja.pdf</a>
 * \n <a href="https://www.rosettacommons.org/manuals/rosetta3.2_user_guide/doxygen_tips.html">Doxygen tips</a>
 */


#include "usscalc.h"

//ppo1: stx, lge, adr, (word1: pkeHi, pkeLo), (word2: indHi, indLo), (word3: pwe1Hi, pwe1Lo), (word4: pwe2Hi, pwe2Lo), pzd1Hi, pzd1Lo, bcc
//ppo2: pke, ind, pwe (1+2), pzd1, pzd2, pzd3, pzd4, pzd5, pzd6
//ppo3: pzd1, pzd2
//ppo4: pzd1, pzd2, pzd3, pzd4, pzd5, pzd6
//ppo5: pke, ind, pwe (1+2), pzd1, pzd2, pzd3, pzd4, pzd5, pzd6, pzd7, pzd8, pzd9, pzd10
#define ppo 1

# define mirror 0

# define pkw 0

// AK: bit 15-12 (0-f << 1111 0000 0000 0000) - Auftrag oder Antwort-ID
// 1 Request parameter
// 2 Change parameter value (word) [RAM only]
// 3 Change parameter value (double word) [RAM only]
// 4 Request description element
# define AK 0x00

// SP: bit 11 (0000 1000 0000 0000) - Spontanmeldebearbeitung
# define mySP 0

// PNU: bit 0-10 (0000 0111 1111 1111) - parameter-nummer (to nie jest ilosc slow PKW_ANZ)
# define PNU 0x12bc

// PNEex: bit 15-12
# define PNUex 0x00

// IDX: bit 0-7 (1111 1111) - array index (subindex)
# define IDX 0x00

uint8_t calcBCC() {
	uint8_t previous = 0;
	uint8_t i = 0;
	do {
		previous = previous ^ myTelegram[i];          // XOR
		i++;
	} while (i < 13);

	return previous;
}

// ver 2.04
void prepTelegram(uint16_t myPNU) {

	// stx, lge, adr,
	// pke: pkeHi, pkeLo,
	// ind: indHi, indLo,
	// pwe1: pwe1Hi, pwe1Lo,
	// pwe2: pwe2Hi, pwe2Lo,
	// pzd1: pzd1Hi, pzd1Lo,
	// bcc

	myTelegram[0] = 0x02;			// indicates the start of a message
	myTelegram[1] = 0x0c;			// length

	// address of the slave node
	myTelegram[2] = (0x00 | (mirror << 6));          // address: the number of RS485 slave-device

	// PKE: parameter number (PNU)
	myPNU = myPNU | 0x1000;          // set 'response' bit
	myTelegram[3] = ((0 | myPNU | (AK << 12) | (mySP << 11)) & 0xff00) >> 8;
	myTelegram[4] = (0 | myPNU | (AK << 12) | (mySP << 11)) & 0x00ff;          // AK

	// IND: for MicroMaster non-significant
	myTelegram[5] = ((PNUex << 12) & 0xff00) >> 8;
	myTelegram[6] = IDX & 0x00ff;          // command

	// PWE1: 1st parameter value, high-order word
	myTelegram[7] = 0x00;
	myTelegram[8] = 0x00;

	// PWE2: 2nd parameter value, low-order word
	myTelegram[9] = 0x00;
	myTelegram[10] = 0x00;

	// PZD1: control status word
	myTelegram[11] = 0x00;
	myTelegram[12] = 0x00;

	// control sum
	myTelegram[13] = calcBCC();
}

uint16_t getValue(uint16_t myParam) {
	uint8_t *mmResponsePtr;
	uint16_t myShort;

	prepTelegram(myParam);
	mmResponsePtr = RS485_QueryTelegram(myTelegram);			// send query and get response (14 bytes)
	myShort = (mmResponsePtr[7] << 8) | mmResponsePtr[8];		// bytes [7] and [8] are the response value

	return myShort;
}


uint16_t * getAllValues(uint16_t* mmParametersArr, uint8_t length) {
	uint8_t i;
	static uint16_t myValueArray[127];					// must be declared static and fix size
	for (i = 0; i < length; i++) {
		// wait();
		myValueArray[i] = getValue(mmParametersArr[i]);
	}
	heartbeat++;										// still alive
	return myValueArray;
}
