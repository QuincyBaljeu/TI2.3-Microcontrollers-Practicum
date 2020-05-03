/*
 * PracticumWeek1.c
 *
 * Created: 2/12/2020 2:08:43 PM
 * Author : qbalj
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8E6
#define BIT(x) (1 << (x))

void B2();
void B3();
void B5();
void wait(int);

int b5Animation[] = {
	0b00000000,
	0b10000000,
	0b10100000,
	0b10101000,
	0b10101010,
	0b10101011,
	0b10101111,
	0b10111111,
	0b11111111,
	0b00000000
};

int main(void)
{
	B5();
}
void B2()
{
	DDRD = 0b11111111; //Set pins of PORTD to output
	while(1)
	{
		PORTD = BIT(7);	//write 00000010 to PORTD
		wait(500);
		PORTD = BIT(6); //write 00000100 to PORTD
		wait(500);
	}
}

void B3()
{
	DDRD = 0b11111111; //Set pins of PORTD to output
	DDRC = 0b00000000; //Set pins of PORTC to input
	
	while(1)
	{
		if(PINC & 1) //If PORTD0 is pressed
		{
			wait(200);
			PORTD ^= BIT(7);	//Toggle PORTD7
		} 
		else 
		{	
			wait(200);
			PORTD &= ~BIT(7);	//Turn off PORTD7
			
		}
	}
}

void B5()
{
	DDRD = 0b11111111; //Set pins of PORTD to output
	
	while(1)
	{
		for(int i = 0; i < 9; i++ )
		{
			PORTD = b5Animation[i];
			wait(500);
		}	
		
	}
} 

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}
