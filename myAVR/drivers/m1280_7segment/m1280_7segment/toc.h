 
 /*!
 * \file toc.h
 * \brief The BCD 7-segment display main documentation page.
 */
 
 /**
 @mainpage The BCD 7-segment display driver for ATmega1280 microcontroller
 
   @section Description
	 <p>
	 The main loop increases continuously a float value by 0.01 every 300 ms. <BR>
	 Then an array for the display is calculated in the display_7_segment() function. <BR>
	 Finally this array is being displayed in the IRQ routine, generated by a timer 0.
	 </p>
  
 <HR>
 @version 1.3
 @date 29.04.2015
 @author pk
 */
