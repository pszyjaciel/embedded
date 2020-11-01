	//
		//enum state
		//{
			//stop_motor,		// 0
			//start_motor,	// 1
			//leftRot,		// 2
			//rightRot,		// 3
		//};
	//
	//uint8_t isPressedAndReleased(uint8_t sw)
	//{
		//// sw jest 1 czyli zwolniony
		//while ((PINC & sw) == 1)
		//{
			//state++;
			//
			//lcd_gotoxy(0, 1);
			//lcd_puts("state: ");
			//itoa(state, buf, 16);
			//lcd_puts(buf);
			//lcd_putc(' ');
			//
		//}
		//return 0;
	//}
	//
	//uint8_t isPressed(uint8_t sw)
	//{
		//// sw jest 1 czyli zwolniony
		//if ((PINC & sw) == 1)
		//{
			//state = stop_motor;
			//
			//lcd_home();
			//lcd_puts("sw1: ");
			//itoa(PINC & sw, buf, 16);
			//lcd_puts(buf);
			//lcd_putc(' ');
			//
			//lcd_gotoxy(0, 1);
			//lcd_puts("state: ");
			//itoa(stop_motor, buf, 16);
			//lcd_puts(buf);
			//lcd_putc(' ');
			//return 0;
			//
		//}
		//
		//// sw jest 0 (czyli wcisniety)
		//else
		//{
			//state = start_motor;
			//
			//lcd_home();
			//lcd_puts("sw1: ");
			//itoa(PINC & sw, buf, 16);
			//lcd_puts(buf);
			//lcd_putc(' ');
			//
			//lcd_gotoxy(0, 1);
			//lcd_puts("state: ");
			//itoa(state, buf, 16);
			//lcd_puts(buf);
			//lcd_putc(' ');
			//return 1;
		//}
	//}
	//
	//
	//
	
	//if (PINC == 0xfe)			// wcisniety sw0
	//{
	//state = leftRot;
	//PORTF = 0b00000001;		// wlacz lewe obroty
	//}
	//
	//else if (PINC == 0xfd)		// wcisniety sw1
	//{
	//PORTF = 0b00000010;		// wlacz prawe obroty
	//}
	//
	//else
	//{
	//PORTF = 0b00000000;		// wylacz silnik
	//}
	
	
	//	isPressedAndReleased(1);
	
	//while ((PINC & 1) == 1)  // czekaj na wcisniecie sw1
	//{
	//PORTF = 0b00000001;		// wlacz lewe obroty
	//}
	//
	//
	//while ((PINC & 1) == 1)  // czekaj na wcisniecie sw1
	//{
	//PORTF = 0b00000010;		// wlacz prawe obroty
	//}
	//
	//
	//
	//while ((PINC & 1) == 1)  // czekaj na wcisniecie sw1
	//{
	//PORTF = 0b00000000;		// wylacz silnik
	//}
	//
	