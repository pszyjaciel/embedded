
/**
 * @mainpage
 * \section desc_sec Description:
 * This project is a PC application that runs on the computer, together with mySQL-server.
 * \n It reads incomming messages from RS232-port on PC, formats them as a SQL-statement and puts it into the database.
 *
 * \subsection detail_subsec Details:
 * Every 5 seconds arrive new data from MicroMaster on serial port of PC. There is not any special protocol for data,
 * but only simple rules. \n Every packages is in form of \b register:value and repeats until all registers has been transfered.
 * The application reads the input until it becomes empty. \n Then parsing of the aquired data is nescessary to make it
 * possible to store them into a database. The raw-data are stored as they are, without any additional check.
 *
 * \subsection hware_subsec Hardware:
 * The data will not arrive somehow. It is nescessary to have a hardware installed that will send periodically data
 * to the serial port of PC. \n This task will be realized by an Ethernut board. It is a PCB with a microcontroler
 * on board of AVR family here ATMEGA128, with static memory of 32kB and 2 serial ports. \n It has also an Ethernet
 * chip from Realtek that makes it possible to connect the board to the Ethernet-network.
 *
 * To get more deeper into this board this link depictures his content:
 * <a href="../../../rs485/resources/Hardware/enut13h_sch.pdf">enut13h_sch.pdf</a>
 *
 * \n VS2010 project in eclipse. Must be compiled from within Visual Studio Command Prompt (2010).
 * \n Copy the libmysql.dll to the exe-folder before run it.
 * \section links_sec Links:
 * <a href="https://www.stack.nl/~dimitri/doxygen/manual/preprocessing.html">doxygen preprocessing.html</a>
 * \n <a href="https://romanegloo.wordpress.com/2012/03/29/generating-a-callgraph-by-using-doxygen-and-graphviz-13/">Generating a callgraph by using Doxygen and Graphviz</a>

 \tableofcontents
 */

/** \page page1 Hardware
  Leading text.
  \section sec An example section
  This page contains the subsections \ref subsection1 and \ref subsection2.
  For more info see page \ref page2.
  \subsection subsection1 The first subsection
  Text.
  \subsection subsection2 The second subsection
  More text.
*/

/** \page page2 Images
  Leading text.
  Even more info.
*/

/**
  \page page3 References
  Even more references.
*/


