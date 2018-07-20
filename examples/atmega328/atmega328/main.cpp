/*
 * atmega328.cpp
 *
 * Created: 02-12-2017 14:27:43
 * Author : Pratik (Jeffy)
 */ 

#include <avr/io.h>

// clock to 20 MHz
#define F_CPU 20000000UL

#include <util/delay.h>

#define BAUD_RATE 9600

//#define BAUD_NUM (F_CPU/(16 * BAUD_RATE))-1

#define BAUD_NUM 0x81

// initialize usart 
void usart_init();

// send 'ch' through usart port
void usart_send(uint8_t ch);

// send position and value to update bit
void updateBit(uint8_t pos, uint8_t value);

int main(void)
{
    /* Replace with your application code */
	// we are testing with 4 seven segment 
	uint8_t v[4] = {'0', '0', '0', '0'};	//0,0,0,0
	usart_init();	
    while (1) 
    {
		// if next least value will exceed 9
		if(v[0] == '9')			
		{
			uint8_t i = 0;
			// reset all higher bits that are 9
			while(v[i] == '9')	
			{
				updateBit(i, '0');	
				v[i] = '0';
				if(i == 3)
				{
					i = 0;
					break;
				}
				i ++;
			}
			v[i] ++;
			//update next below 9 value
			updateBit(i, v[i]);
			// one second delay
			_delay_ms(1000); 		
		}
		// normal updating least bit
		v[0] ++;
		updateBit(0, v[0]);
		_delay_ms(1000);
    }
}

void updateBit(uint8_t pos, uint8_t value)
{
	usart_send(pos);							// send position (0 - 7)
	usart_send(value);							// send value
}

void usart_init()
{
	UCSR0B = (1 << TXEN0);						// enable transmitter
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);		// 8 bit data packet
	UBRR0L = BAUD_NUM;							// set baud rate
}

void usart_send(uint8_t ch)
{
	while(!(UCSR0A&(1<<UDRE0)));				// wait while UDR is not empty
	UDR0=ch;									// set UDR
}


