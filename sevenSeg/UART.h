

#ifndef AVRIO
	#define AVRIO 1
	#include <avr/io.h>
#endif

#ifndef AVRINTERRUPT
	#define AVRINTERRUPT 1
	#include <avr/interrupt.h>
#endif

#ifndef F_CPU
	#define F_CPU 20000000UL
#endif

#ifndef BAUD_RATE
	#define BAUD_RATE 9600		//for 9600 baud rate
#endif

#ifndef BAUD_NUM
//	#define BAUD_NUM (F_CPU/(16*BAUD_RATE))-1
	#define BAUD_NUM 0x76		// as observed value for above expression in simulator in Atmel Studio
#endif
class UART
{
	public:
		void init()
		{
			UCSRB = (1 << RXEN) | (1 << RXCIE);					//enable receive, and receive interrupt
			UCSRC = (1 << 7) | (1<<UCSZ1) | (1 << UCSZ0);		//7 is for URSEL
																//8 bit data, no parity, 1 stop bit
			UBRRL = BAUD_NUM;									//U2X is set 
		//	sei();
		}
		
		uint8_t receive()
		{
			//while(! (UCSRA) & (1 << RXC));					//no longer polling
			return UDR;											//return received content
		}
		
};