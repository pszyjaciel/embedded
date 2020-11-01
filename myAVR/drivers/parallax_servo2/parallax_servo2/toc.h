 
 /*!
 * \file toc.h
 * \brief The Parallax Servo main documentation page.
 */
 
 /**
 @mainpage Parallax Servo Driver for ATmega1280 microcontroller
  
  @section Content
  -# @ref Connections
  -# @ref Description
  -# @ref Results
  
  <table>
	  <tr>
		  <td>
			 <p> The driver works with Pulse Width Modulation on timer OC1C - output PB7.<BR>
			 When powering on the impuls width is set to 1.5ms that positions the servo in the middle.<BR>
			 The time of an impuls \a[t<SUB>1</SUB>] for angle of -90&deg; is 0.75ms, while the time for the
			 angle of +90&deg; is 2.25ms. <BR>
			 The period \a[t<SUB>p</SUB>] for repeating impulses is 20ms. Please also refer to the belowed picture. </p>
		  </td>
		  <td> @image html servo.png </td>
	  </tr>
  </table>
  
 @image html time_period2.png
 <hr/>
 
 @section Connections Connections
 <p> The servo can be powered from the EasyAVR board and must be connected to the expansion slot with these pin-outs:
 - Servo connector:
 + pin 26: signal (white)
 + pin 31: +5V (red)
 + pin 32: GND (black)
 </p>
 @image html u:/ICT/6th_semester/hwpi1/handin2/parallax_servo2/parallax_servo2/doxygen/images/connection.png 
 @note It was observed that the power regulator installed on the AVR board gets hot while testing with the time 
 period other than 20ms. \n
 No further meassurements have been performed with this issue. <p>\n</p>

 @section Description Work description
 <p> The PWM can be obtained with many modes. The mode 15 has been used for this driver.
 However the mode 9 also has been tested with this timer. </p>
 @code
 TCCR1B |= (1 << WGM13);				// mode 15
 TCCR1B |= (1 << WGM12);
 TCCR1A |= (1 << WGM11);
 TCCR1A |= (1 << WGM10);
 @endcode
 <p> For the proper work of servo the setting parameters TOP, MIN, CENTER and MAX must be calculated before. \n Parameters
 MIN and MAX include information about the impuls-time. The TOP parameter defines the time period. \n
 (please refer to the picture above). \n </p>
 @code
 #define TOP (((F_CPU/50)/PRESCALER) - 1)		// 50Hz
 #define MIN (TOP/(20/0.75))						// 20ms = 50Hz
 #define CENTER (TOP/(20/1.5))					// brackets make the integer
 #define MAX (TOP/(20/2.25))
 @endcode
 <p>The content of register OCR1A defines the maximum value for the counter, <BR>
 which is increased until it has reached the TOP. \n
 The value in register OCR1C is continuously compared with the value inside of counter. <BR>
 Are they equal the output OC1C change his level. This depends on the settings of COM1C1
 and COM1C0 in the TCCR1A register. <BR>
 Please also refer to the datasheet <A HREF="../docs/p167-168.pdf"> pages: 167-168.</A></p>
 @code
 TCCR1A |= (1 << COM1C1);						// Toggle OC1C on Compare Match
 TCCR1A &= ~(1 << COM1C0);
 OCR1A = TOP;									// period: 50Hz for prescaller 64
 OCR1C = CENTER;
 @endcode
 <p>\n</p>
 <HR>
 
 @section Results Results
 <p> The driver sends with frequency of 50Hz an impuls to the servo setting his rotor on desired position. \n
 The result for the PWM in mode 15 has been observed with the osciloscope and is showed below: </p>
 
@image html period.png 

<A HREF="../images/nexttime.jpg ">Get a high resolution image hier.</A></p>

 <HR>
 @version 1.1.2
 @author pk
 */

