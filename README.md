# RS232-synchronous-chat
Chat application with synchronous communication via [Recommended Standard 232](https://en.wikipedia.org/wiki/RS-232).

## Project files:
- <code>'rs232.c'</code> contains functions for:
	- rs232_open
	- rs232_close
	- rs232_read
	- rs232_write 

- <code>'rs232.h'</code> contains:
	- structure rs232_obj
	- declaration of rs232 functions

- <code>'232chat.c'</code> contains:
	- ReadThread func 
		> сonstantly waiting and reading a message from another user 
  	- main
  	 	> a
      		> select COm port, user name, laucnh ReadThread func, reading a user message and sending it.

## Overview
Connect 2 computers via rs232 and run the code on each computer.
<br>Find the COM port to which each computer is connected and enter it into the program.
<br>Specify your nicknames and enjoy chatting.
<br>
<br>You can also connect the rs232 to 2 different ports on the same pc and run 2 windows in the program.
<br>
<br>You can install any virtual serial port driver if you do not have a physical rs232.
