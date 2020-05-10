/*
 * PracticumWeek3.c
 *
 * Created: 5/9/2020 11:41:43 AM
 * Author : qbalj
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "stdio.h"
#include <avr/interrupt.h>

#define F_CPU 8e6
#define LCD_E 	3
#define LCD_RS	2

void B1();
void B2();
void writeLcd();
void init();
void display_text(char*);
void writeLcdData(unsigned char);
void wait(int);

int main(void)
{
	B1();
}

void B1()
{
    DDRD = 0b0000001;
    TCCR2 = 0b00000111; 
    
    DDRB = 0b00000000; // PORTB is output
    init();
    
	int counterIn;
	
    while (1)
    {
	    PORTD = TCNT2;
		counterIn = TCNT2;
		
		char counterString[16];
		sprintf(counterString, "%u", counterIn);
		
		display_text(counterString);
    }	
	
}

ISR(TIMER1_COMPA_vect)
{
	PORTD = 0b00000001;
	wait(15);
	PORTD = 0b00000000;
	wait(25);
}

void B2()
{
	DDRD = 0b11111111; //set PORTD to output
	
	cli(); // Disable interrupts

	 TCCR1A = 0;
	 TCCR1B = 0;
	 TCNT1  = 0;
	
	 OCR1A = 15624;
	 
	 TCCR1B |= (1 << WGM12);
	
	 TCCR1B |= (1 << CS12) | (1 << CS10);
	
	 TIMSK1 |= (1 << OCIE4A);

	 sei();//allow interrupts
	
}

void writeLcd() {
	PORTC |= (1<<LCD_E);
	wait(1);
	PORTC &= ~(1<<LCD_E);
	wait(1);
}

void init() {
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	writeLcd();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	writeLcd();
	PORTC = 0x80;
	writeLcd();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	writeLcd();
	PORTC = 0xF0;
	writeLcd();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	writeLcd();
	PORTC = 0x60;
	writeLcd();
}

void display_text(char *str){
	for(;*str; str++){
		writeLcdData(*str);
	}
}

void writeLcdData(unsigned char byte) {
	
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	writeLcd();

	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	writeLcd();
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
