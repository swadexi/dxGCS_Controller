#include <avr/io.h>
#include <avr/interrupt.h>
#include "all.h"
int VALUE;

#define TRUE	1
#define FALSE	0
char char_data ;
#include <util/delay.h>




/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

void init_serial(char channel)
{
	if (channel == 0)
	{
	UBRR0H = 0;									//BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	UBRR0L = 12; 								//207;//103;//(BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);	
	}
	else if(channel == 1)
	{
	UBRR1H = 0;									//BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	UBRR1L = 103; 								//(BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UCSR1B = (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);
	UCSR1C = (1<<USBS1)|(3<<UCSZ10);	
	}
	sei();
}


/***************************/
void write(char channel, unsigned char c)
{	  if (channel == 0)
      {while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it	
      UDR0 = c;} // Echo back the received byte back to the computer
	  else if (channel == 1)
      {while ((UCSR1A & (1 << UDRE1)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it	
      UDR1 = c;} // Echo back the received byte back to the computer

}
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

unsigned char read(char channel )
{	
	if (channel == 0){
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	var = UDR0;}
	else if (channel == 1){
	while ( !(UCSR1A & (1<<RXC1)) )
	;
	var = UDR1;}
	return var;
}

void string(char channel, char *ss)
{
	while (*ss)
	{
	write (channel,*ss);
	ss++;
	}
}

void ascii(char channel, int VALUE, char digit)
{
	
		satuan = (VALUE%10)+0x30;
		puluhan = (VALUE%100)/10;
		puluhan += 0x30;		 
		ratusan = (VALUE % 1000)/100;
		ratusan +=0x30;
		char ribuan = (VALUE%10000)/1000;
		ribuan +=0x30;	
		char puluhanribu = (VALUE%100000)/10000;
		puluhanribu +=0x30;
			 
		if(digit == 1) 
		{			 
			 write(channel,satuan);	
		}
		else if(digit == 2)
		{			
			 write(channel,puluhan);
			 write(channel,satuan);
		
		}	 
		else if(digit == 3)
		{	
			 write(channel,ratusan);
			 write(channel,puluhan);
			 write(channel,satuan);
		}
		else if(digit == 4)
		{
			write(channel,ribuan);
			 write(channel,ratusan);
			 write(channel,puluhan);
			 write(channel,satuan);
		}	 

		else if(digit == 5)
		{
			 write(channel,puluhanribu);
			 write(channel,ribuan);
			 write(channel,ratusan);
			 write(channel,puluhan);
			 write(channel,satuan);
		}

			
	
}

