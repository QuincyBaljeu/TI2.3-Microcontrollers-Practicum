/*
 * PracticumWeek2.c
 *
 * Created: 2/12/2020 12:46:49 PM
 * Author : qbalj
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

void B3(int);
void wait(int);

unsigned int numbers[] = {
	0b00111111,
	0b00110000,
	0b01011011,
	0b01111001,
	0b01110100,
	0b01101101,
	0b01101111,
	0b00111000,
	0b01111111,
	0b01111101,
	0b01111110,
	0b01111111,
	0b00001111,
	0b00111111,
	0b01001111,
	0b01001110,
};

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		
		B3(1);
		wait(1000);
		B3(10);
		wait(1000);
		B3(16);
		wait(1000);
		B3(-1);
		wait(1000);
		B3(7);
		wait(1000);
		
		
    }
}

void B3(int digit)
{
	DDRD = 0b11111111;
	
	if (digit > 15 || digit < 0)
	{
		PORTD = numbers[14];
	}
	else
	{
		 PORTD = numbers[digit];
	}
	
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

