/*
 * sevenSeg.cpp
 *
 * Created: 24-11-2017 20:30:35
 * Author : Pratik (Jeffy)
 */ 

#include <avr/io.h>
#define AVRIO 1

#include "SevenSeg.h"

#include "UART.h"

SevenSeg ss;

UART serial;		

// Interrupt Service Routine (ISR) to handle uart receive complete
// recvd is a array of size 2, 
// first element will contain cmd 
// and second element will contain data
// point will be used to check number of bytes received

uint8_t recvd[2];
uint8_t point = 0;

ISR(USART_RX_vect)	
{
	recvd[point++] = serial.receive();
	if(point >= 2)
	{
		ss.execute(recvd);
		point = 0;
	}
}

int main(void)
{
	serial.init();
	DDRB = 0xFF;
	DDRD = 0xFF;
    /* Replace with your application code */
	//extra
	//uint8_t temp_bit = 0;
	//uint8_t temp_bv = 0;
	//uint8_t temp_d = 0;
	ss.cmdCall(0, 65);
	//ss.cmdCall(1, 66);
	//ss.cmdCall(2, 67);
	//ss.cmdCall(3, 68);
	//ss.cmdCall(8, 0x05);
	/*//extra end	*/
    while (1)
	{
	    ss.display();
	/*	temp_d ++;
		if((temp_d % 1000) == 0)
		{
			ss.cmdCall(8, 0x00);
	 	}
	*/
    }
}

