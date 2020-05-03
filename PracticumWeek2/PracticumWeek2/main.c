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
	0b00111111,		//0
	0b00110000,		//1
	0b01011011,		//2	
	0b01111001,		//3
	0b01110100,		//4
	0b01101101,		//5		
	0b01101111,		//6
	0b00111000,		//7
	0b01111111,		//8
	0b01111101,		//9
	0b01111110,		//A
	0b01111111,		//B
	0b00001111,		//C
	0b00111111,		//D
	0b01001111,		//E
	0b01001110,		//F
};

int main(void)
{
    /* Replace with your application code */
	while(1)
	{
		for(int i = 0; i <= 16; i++){
			B3(i);
			wait(750);
		}
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

