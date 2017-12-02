
#ifndef AVRIO
	#define AVRIO 1
	#include <avr/io.h>
#endif

#ifndef F_CPU
	#define  F_CPU 20000000UL 
#endif

#include <util/delay.h>

#include "code.h"

//number of digits
#define SEG_NUM 4

//Ground bits of 4 seven segments
#define E_1 2
#define E_2 3
#define E_3 4
#define E_4 5

const uint8_t codes[36] = {S_0, S_1, S_2, S_3, S_4, S_5, S_6, S_7, S_8, S_9, S_A, S_B, S_C, S_D, S_E, S_F, S_G, S_H, S_I, S_J, S_K, S_L, S_M, S_N, S_O, S_P, S_Q, S_R, S_S, S_T, S_U, S_V, S_W, S_X, S_Y, S_Z};

const uint8_t gnd[SEG_NUM] = {E_1, E_2, E_3, E_4};


class SevenSeg
{
	uint8_t sevSeg[SEG_NUM] = {0, 0, 0, 0};
	uint8_t gpin[SEG_NUM] = {1, 1, 1, 1};
	public:
	void cmdCall(uint8_t cmd, uint8_t data)
	{
		switch(cmd)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
				updateBit(cmd, data);
				break;
			case 8:
				partialSwitch(data);
				break;
			case 9:
				switchnf(data);
				break;
			case 0xA:
				clearout(data);
		}
	}
	void display()
	{
		for(int i = 0;i < SEG_NUM;i ++)
		{
			PORTB = sevSeg[i];
			PORTD = ~(gpin[i] << gnd[i]);
			_delay_ms(5);
			
		}
	}
	
	void updateBit(uint8_t place, uint8_t value) // X(0:7) xxxxxxxx
	{
		if(place >= SEG_NUM)		//7 segment digit doesn't exist
		{
			return;
		}
		if(value > 15)	// non - numeric value, it's alphabet
		{
			if((value > 64) && (value < 91))		//A-Z - (65:90) - 65 + 10
			{
				value -= 55;
			}
			else if((value > 96) && (value < 123))	//a-z - (97:122) - 97 + 10
			{
				value -= 87;
			}
			else     // garbage - make it zero
			{
				value = 0;
			}
		}
		sevSeg[place] = codes[value];
	}
	void partialSwitch(uint8_t pattern)	//X8 xxxxxxxx
	{
		if(pattern == 0xFF)
		{
			switchnf(0xFF);
			return;
		}
		if(pattern == 0x00)
		{
			switchnf(0x00);
			return;
		}
		for(uint8_t i = 0; i < SEG_NUM; i ++)
		{
			//uint8_t op = (1 << i);
			uint8_t r = pattern & (1 << i);
			if(r == 0)
			{
				gpin[i] = 0;
			}
			else
			{
				gpin[i] = 1;
			}
		}
	}

	void switchnf(uint8_t d)	//X9 dddddddd
	{
		uint8_t r;
		if(d == 0)
		{
			r = 0;
		}
		else
		{
			r = 1;
		}
		for(uint8_t i = 0; i < SEG_NUM; i ++)
		{
			gpin[i] = r;
		}
	}
	
	void clearout(uint8_t pattern)
	{
		if(pattern == 0xFF)
		{
			for(uint8_t i = 0; i < SEG_NUM; i ++)
			{
				gpin[i] = 1;
			}
			return;
		}
		for(uint8_t i = 0;i < SEG_NUM; i ++)
		{
			uint8_t r = pattern & (1 << i);
			if(r != 0)
			{
				sevSeg[i] = S_0;
			}
		}
	}
	
	void execute(uint8_t recvd[2])
	{
		//uint8_t cmd = recvd[0] & 0x0F;	//filter 4 MSB bits of command
		//uint8_t data = recvd[1];			//data
		//cmdCall(cmd, data);				//call command
		cmdCall((recvd[0] & 0x0F), recvd[1]);	//shortcut for above steps
	}
	
};