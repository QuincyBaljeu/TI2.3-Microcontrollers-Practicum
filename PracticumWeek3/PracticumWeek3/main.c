/*
 * PracticumWeek3.c
 *
 * Created: 5/9/2020 11:41:43 AM
 * Author : qbalj
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8e6
#define LCD_E 	3
#define LCD_RS	2

void writeLcd();
void init();
void display_text(char*);
void writeLcdData(unsigned char);
void wait(int);

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
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
