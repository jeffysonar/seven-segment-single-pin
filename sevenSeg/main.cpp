/*
 * sevenSeg.cpp
 *
 * Created: 24-11-2017 20:30:35
 * Author : Pratik (Jeffy)
 */ 
#ifndef AVRIO
	#define AVRIO 1
	#include <avr/io.h>
#endif

#include "SevenSeg.h"
int main(void)
{
	SevenSeg ss;
	DDRB = 0xFF;
	DDRD = 0xFF;
    /* Replace with your application code */
	uint8_t temp_bit = 0;
	uint8_t temp_bv = 0;
	uint8_t temp_d = 0;
	ss.cmdCall(0, 65);
	ss.cmdCall(1, 66);
	ss.cmdCall(2, 67);
	ss.cmdCall(3, 68);
	ss.cmdCall(8, 0x05);
    while (1) 
    {
	    ss.display();
		temp_d ++;
		if((temp_d % 1000) == 0)
		{
			ss.cmdCall(8, 0x00);
	 	}
    }
}

