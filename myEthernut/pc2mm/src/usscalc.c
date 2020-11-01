/**
 * @page referenced_documents This Page references to some documents about USS protocol.
 * \section links_sec Links:
 * \n <a href="../../literature/USS2LabVIEW.pdf">USS2LabVIEW.pdf</a>
 * \n <a href="../../literature/Cykliczna i acykliczna komunikacja.pdf">Cykliczna i acykliczna komunikacja.pdf</a>
 * \n <a href="https://www.rosettacommons.org/manuals/rosetta3.2_user_guide/doxygen_tips.html">Doxygen tips</a>
 */

#include "usscalc.h"

/**
 * @param ppo1
 * - ppo1: stx, lge, adr, (word1: pkeHi, pkeLo), (word2: indHi, indLo), (word3: pwe1Hi, pwe1Lo), (word4: pwe2Hi, pwe2Lo), pzd1Hi, pzd1Lo, bcc
 * - ppo2: pke, ind, pwe (1+2), pzd1, pzd2, pzd3, pzd4, pzd5, pzd6
 * - ppo3: pzd1, pzd2
 * - ppo4: pzd1, pzd2, pzd3, pzd4, pzd5, pzd6
 * - ppo5: pke, ind, pwe (1+2), pzd1, pzd2, pzd3, pzd4, pzd5, pzd6, pzd7, pzd8, pzd9, pzd10
 */
#define ppo 1

# define mirror 0

/**
 * @param AK
 * AK: bit 15-12 (0-f << 1111 0000 0000 0000) - Auftrag oder Antwort-ID
 * - 1: Request parameter
 * - 2: Change parameter value (word) [RAM only]
 * - 3: Change parameter value (double word) [RAM only]
 * - 4: Request description element
 */
# define AK 0x00

/**
 * SP: bit 11 (0000 1000 0000 0000) - Spontanmeldebearbeitung, not used
 */
# define SP 0

/**
 * @param PNU
 * PNU: bit 0-10 (0000 0111 1111 1111) - parameter-nummer (this is not the number of words PKW_ANZ)
 */
# define PNU 0x12bc

/**
 * @param PNUex
 * PNEex: bit 15-12
 */
# define PNUex 0x00

/*
 * @param IDX
 * IDX: bit 0-7 (1111 1111) - array index (subindex)
 */
# define IDX 0x00

uint8_t* sendTelegram()
{
	uint8_t i;

	// display telegram
//	for (i = 0; i < sizeof(myTelegram); i++) {
//		printf("%02x ", myTelegram[i]);
//	}

	printf("sendTelegram(): sizeof(myTelegram): %d \n", sizeof(myTelegram));
	sendReadTelegram(myTelegram);

	return myTelegram;
}

/**
 * @brief Function calculates the BCC check sum by simply xoring the actual with a previous value.
 * @return 8-bit unsigned value
 */
uint8_t calcBCC()
{
	uint8_t previous = 0;
	uint8_t i = 0;
	do
	{
		previous = previous ^ myTelegram[i];          // XOR
		i++;
	} while (i < 13);

	return previous;
}

/**
 * @brief ver 2.03
 * Function creates a telegram message according to the USS-protocol.
 * \n The message is 14-byte long and consists of:
 * - 00. byte: STX, start of telegram
 * - 01. byte: LGE, length of telegram
 * - 02. byte: ADR, device number
 * - 03. byte: PKEhi, 1. word, register number
 * - 04. byte: PKElo, AK, SP
 * - 05. byte: INDhi, PKW, 2. word, page index
 * - 06. byte: INDlo, subindex
 * \n ----------------- start of PKW -----------------
 * - 07. byte: PWE1hi, 3. word
 * - 08. byte: PWE1lo, 1st parameter value, high-order word
 * - 09. byte: PWE2hi, PKW, 4. word
 * - 10. byte: PWE2lo, 2nd parameter value, low-order word
 * \n ------------------ end of PKW ------------------
 * \n ----------------- start of PZD -----------------
 * The number of PZD words in a USS-telegram is determined by parameter P2012.
 * Request to USS slave: Control word 1(STW1) and main setpoint (HSW)
 * Response to USS master: Status word 1 (ZSW1) and actual value (HIW)
 * - 11. byte: PZD1hi, STW/ZSW
 * - 12. byte: PZD1lo, HSW//HIW
 * \n -------------------end of PZD ------------------
 * - 13. byte: BCC check sum of telegrams
 * @param myRegNo number of register
 * @return no return.
 */
void prepTelegram(uint16_t myRegNo)
{
	// indicates the start of a message
	myTelegram[0] = 0x02;
	myTelegram[1] = 0x0c;
	myTelegram[2] = (0x00 | (mirror << 6));          // the number of RS485 slave-device

	myRegNo = myRegNo | 0x1000;          // set 'response' bit
	myTelegram[3] = ((0 | myRegNo | (AK << 12) | (SP << 11)) & 0xff00) >> 8;
	myTelegram[4] = (0 | myRegNo | (AK << 12) | (SP << 11)) & 0x00ff;          // AK

	// PKW, 2. word		- be carefull with bit15 in PNUex
	// bit15-8: page index, bit7-0: subindex
	myTelegram[5] = ((PNUex << 12) & 0xff00) >> 8;
	myTelegram[6] = IDX & 0x00ff;          // command

	// PKW, 3. word		= PWE1 = 1st parameter value, high-order word
	myTelegram[7] = 0x00;
	myTelegram[8] = 0x00;

	// PKW, 4. word     = PWE2 = 2nd parameter value, low-order word
	myTelegram[9] = 0x00;
	myTelegram[10] = 0x00;

	// PZD
	myTelegram[11] = 0x00;          // ZSW while response
	myTelegram[12] = 0x00;

	// control sum
	myTelegram[13] = calcBCC();
}

/**
 * @brief Function returns one parameter value from the MicroMaster
 * @param myRegNo is a 16-bit value that represents the number of MM-register
 * @return A 16-bit value.
 */
uint16_t getValue(uint16_t myRegNo)
{
	prepTelegram(myRegNo);
	sendReadTelegram(myTelegram);
	return (myTelegram[7] << 8) | myTelegram[8];
}

void wait()
{
	uint32_t i;
	for (i = 0; i < 16000000; i++)
	{
		;
	}
}

uint16_t* getAllValues(uint16_t* myParamArr, uint8_t length)
{
	uint8_t i;
	for (i = 0; i < length; i++)
	{
		// wait();
		myParamArr[i] = getValue(myParamArr[i]);
	}
	return myParamArr;
}
