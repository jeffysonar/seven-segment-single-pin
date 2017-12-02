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

#define BAUD_NUM 0x76

void usart_init();

void usart_send(uint8_t ch);

int main(void)
{
    /* Replace with your application code */
	_delay_ms(2500);
	_delay_ms(2500);
	int p = 0;
	int v = 0;	
    while (1) 
    {
		v++;
		_delay_ms(1000);
		usart_send(p);
		_delay_ms(100);
		usart_send(v);
		if(v == 9)
		{
			v = 0;
			p = (p + 1) % 4;
		}
    }
}

void usart_init()
{
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << 7) | (1 << UCSZ00) | (1 << UCSZ01);
	UBRR0L = BAUD_NUM;	
}

void usart_send(uint8_t ch)
{
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=ch;
}


