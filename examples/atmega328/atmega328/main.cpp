/*
 * atmega328.cpp
 *
 * Created: 02-12-2017 14:27:43
 * Author : Pratik (Jeffy)
 */ 

#include <avr/io.h>

#define F_CPU 20000000UL

#include <util/delay.h>

#define BAUD_RATE 9600

//#define BAUD_NUM (F_CPU/(16 * BAUD_RATE))-1

#define BAUD_NUM 0x81

void usart_init();

void usart_send(uint8_t ch);

void updateBit(uint8_t pos, uint8_t value);

int main(void)
{
    /* Replace with your application code */
	//for(int i=0;i<100;i++)
	uint8_t v[4] = {'0', '0', '0', '0'};	//0,0,0,0
	usart_init();
//	_delay_ms(2000);
	//uint8_t p = 0;
	//uint8_t v = '0';//'A';	
    while (1) 
    {
		//usart_send(0xE2);
		//_delay_ms(20);
		if(v[0] == '9')			//9
		{
			uint8_t i = 0;
			while(v[i] == '9')	//9
			{
				updateBit(i, '0');	//0
				v[i] = '0';
				if(i == 3)
				{
					i = 0;
					break;
				}
				i ++;
			}
			v[i] ++;
			updateBit(i, v[i]);
			_delay_ms(1000); 		
		}
		v[0] ++;
		updateBit(0, v[0]);
		_delay_ms(1000);
    }
}

void updateBit(uint8_t pos, uint8_t value)
{
	usart_send(pos);
	usart_send(value);
}

void usart_init()
{
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	UBRR0L = BAUD_NUM;	
}

void usart_send(uint8_t ch)
{
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=ch;
}


