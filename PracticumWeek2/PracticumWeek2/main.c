/*
 * PracticumWeek2.c
 *
 * Created: 2/12/2020 12:46:49 PM
 * Author : qbalj
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8e6
#define LCD_E 	3
#define LCD_RS	2

void B3(int);
void B32();
void B4();
void writeLcd();
void init();
void display_text(char*);
void set_cursor(int);
void lcd_write_command(unsigned char);
void wait(int);

typedef struct  
{
	unsigned int segment;
	unsigned int delay;
} ANIMATION_STEP;

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

ANIMATION_STEP animation[] = {
	{0b00000001, 100},
	{0b00000010, 100},
	{0b01000000, 100},
	{0b00010000, 100},
	{0b00001000, 100},
	{0b01000000, 100},
	{0b00100000, 100},
	{0b00000001, 100}	
};

int main(void)
{
    /* Replace with your application code */
	DDRD = 0xFF;
	
	init();
	
	display_text("YEDI, YOARE");
	
	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		wait( 250 );
	}

	return 1;
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

void B32()
{
	DDRD = 0b11111111; //Set PORTD to output
	DDRC - 0b00000000; //Set PORTC to output
	
	int index = 0;

	while (1)
	{
		if(PINC & 0b00000001)
		{
			if(PINC & 0b00000010)
			{
				index = 0;
			}
			else
			{
				if(index < 15)
				{
					index++;
					B3(index);		
				}
			}
		} 
		else if(PINC & 0b00000010)
		{
			if(PINC & 0b00000001)
			{
				index = 0;	
			}
			else
			{
				if(index > 0)
				{
					index--;
					B3(index);
				}
			}
		}
	}
}

void B4(){
	DDRD = 0b11111111; //Set PORTD to output
	
	while(1){
		int i = 0;
		
		while (animation[i].delay != 0)
		{
			PORTD = animation[i].segment;
			wait(animation[i].delay);
				
			i++;
		}
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
		lcd_write_data(*str);
	}
}

/******************************************************************/
void lcd_write_data(unsigned char byte)
/*
short:			Writes 8 bits DATA to lcd
inputs:			byte - written to LCD
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	writeLcd();

	// Second nibble
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

