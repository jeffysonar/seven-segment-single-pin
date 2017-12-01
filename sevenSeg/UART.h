

#ifndef AVRIO
	#define AVRIO 1
	#include <avr/io.h>
#endif
#ifndef BAUD_RATE
	#define BAUD_RATE 0x09		//for 115200 baud rate
#endif
class UART
{
	public:
		void init()
		{
			UCSRB=(1<<RXEN)|(1<<TXEN);
			UCSRC=(1<<7)|(1<<UCSZ1)|(1<<UCSZ0);		//7 is for URSEL
			UBRRL=BAUD_RATE;
		}
		void send(uint8_t ch)
		{
			while(!(UCSRA&(1<<UDRE)));
			UDR=ch;
		}
		uint8_t receive()
		{
			while(!(UCSRA)&(1<<RXC));
			return UDR;	
		}
		
};