


# define N5110_RST_SET PORTB |= (1 << PB5)	
# define N5110_RST_CLR PORTB &= ~(1 << PB5)
# define N5110_DC_SET PORTB |= (1 << PB4)	
# define N5110_DC_CLR PORTB &= ~(1 << PB4)
# define N5110_BL_SET PORTB |= (1 << PB3)	// backlight (OC0A) 
# define N5110_BL_CLR PORTB &= ~(1 << PB3)
# define N5110_CE_SET PORTB |= (1 << PB6)	
# define N5110_CE_CLR PORTB &= ~(1 << PB6)

//1: VCC (+3.3 up to 5.0)	czerwony //2: GND			czarny //3: SCE - PB6		brazowy //4: RST - PB5		pomarancz //5: D/C - PB4		zolty//6: DN(MOSI) - PB2	niebieski    pin21//7: SCLK - PB1		fioletowy	 pin20//8: LED - PB3		bialy
//					zielony nie podlaczony


void Delay_MS(uint16_t dMS);
void Port_Init(void);
void SPI_MasterInit(void);
uint8_t SPI_MasterTransmit(unsigned char cByte);
void N5110_WriteByte(uint8_t cByte, uint8_t cCommand);
void N5110_Clear(void);
void N5110_Init(void);
void setPos(int pos);
void printChar(char ch);
void printWord(char *bString);
void N5110_RefreshRam(uint8_t *pcBuff);
void WaitMs(unsigned int ms);
void Timer0_Init(void);



