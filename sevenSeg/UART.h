

#ifndef AVRIO
	#define AVRIO 1
	#include <avr/io.h>
#endif

#ifndef F_CPU
	#define F_CPU 20000000UL
#endif

#ifndef BAUD_RATE
	#define BAUD_RATE 9600		//for 9600 baud rate
#endif

#ifndef BAUD_NUM
//	#define BAUD_NUM (F_CPU/(16*BAUD_RATE))-1
	#define BAUD_NUM 0x81
#endif
class UART
{
	public:
		void init()
		{
			UCSRB = (1 << RXEN) | (1 << RXCIE);					//enable receive, and receive interrupt
			UCSRC = (1<<UCSZ1) | (1 << UCSZ0);					//8 bit data, no parity, 1 stop bit
			UBRRL = BAUD_NUM;									//U2X is set to 0
		}
		
		uint8_t receive()
		{
			return UDR;											//return received content
		}
		
		uint8_t receiveComplete()
		{
			return ((UCSRA) & (1 << RXC));
		}
};