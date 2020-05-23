#include <avr/io.h>
#include <avr/interrupt.h>
#include "typedefs.h"


#define RX_CH1	_BIT(PIND,2)
#define RX_CH2	_BIT(PINB,5)
volatile uint16_t signal_value;
volatile uint16_t signal_value2;

int main()
{
DDRD = 0b11111011;
DDRB = 0b11010000;
PCMSK |=1<<PCINT5; 
MCUCR |= (0<<ISC01) | (1<<ISC00);
GIMSK |= (1<<INT0);
GIMSK |= (1<<PCIE); 
sei();
	while(1)
	{	
		
		if (signal_value > 1550)
		{
			_PORTD4 = 1;
		}
		else
		{
			_PORTD4 = 0;
		}		
	
		if (signal_value2 > 47)
		{
			_PORTD6 = 1;
		}
		else
		{
			_PORTD6 = 0;
		}		
	
	}
}

ISR (SIG_PCINT)
{
	if(RX_CH2)
	{
		TCCR0B |=1<<CS02 ;
		TCNT0 = 0;		
	}
	else if(RX_CH2 == 0)
	{
		TCCR0B =0;
		signal_value2 = TCNT0;		
	}

}
ISR (SIG_INT0)
{
	
	if(RX_CH1)
	{
		TCCR1B |=1<<CS11;
		TCNT1 = 0;	
	}
	else if(RX_CH1 == 0)
	{
		TCCR1B =0;
		signal_value = TCNT1;		
	}
}


