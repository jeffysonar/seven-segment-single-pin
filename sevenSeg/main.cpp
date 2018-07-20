/*
 * sevenSeg.cpp
 *
 * Created: 24-11-2017 20:30:35
 * Author : Pratik (Jeffy)
 */ 

#include <avr/io.h>
#define AVRIO 1

#ifndef AVRINTERRUPT
	#define AVRINTERRUPT 1
	#include <avr/interrupt.h>
#endif

#include "SevenSeg.h"

#include "UART.h"

SevenSeg ss;

UART serial;		

// Interrupt Service Routine (ISR) to handle uart receive complete
// recvd is a array of size 2, 
// first element will contain cmd 
// and second element will contain data

uint8_t recvd[2];

ISR(USART_RX_vect)	
{
	recvd[0] = serial.receive();
	cli();								// disable interrupt globally
										// MCU does that on receiving interrupt, just to clear idea
	uint16_t t = 0;						// our 16-bit timer
	while((! serial.receiveComplete()) &  (t < 0xFFFF))
	{
		t++;							// timer running
	}
	if(t == 0xFFFF)						// checking timeout
	{
		return;
	}
	recvd[1] = serial.receive();		// get data byte
	ss.execute(recvd);					// execute cmd	``	````
	sei();								//restore (enable) interrupts
}

int main(void)
{
	serial.init();
	sei();												//enable interrupt globally
	DDRB = 0xFF;
	DDRD = 0x00;
	for(int i = 0; i < SEG_NUM; i ++)
	{
		DDRD |= (1 << gnd[i]);
	}
    while (1)
	{
	    ss.display();
    }
}

