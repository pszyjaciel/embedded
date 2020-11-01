This BCD driver use the SPI functionality to display a float value on LCD. <br />
Function display_7_segment() prepare an array of patterns to display. <br />
The main loop calls displayFloat() with a float value as parameter. <br />
The displayFloat() will call the display_7_segment() ONLY IF SPI is ready to take the next byte. <br />
Finally the ISR(SPI_STC_vect) send these patterns to the LCD one digit at a time. <br />

The timing is to be find in this file: osci.png <br />
The SPI period is set to ~150usec. <br />
The displayFloat() costs 100usec of uC-time. <br />

![The timing](https://github.com/pszyjaciel/avr/blob/master/myAVR/drivers/m1280_7segment_SPI3/osci.png)


5:35 PM 9/28/2016