#ifndef TYPE_DEFS_H_
#define TYPE_DEFS_H_

#include <stdint.h>

//dxDef.h By Swadexi
//Free To distributed

typedef struct
{
  unsigned int bit0:1;
  unsigned int bit1:1;
  unsigned int bit2:1;
  unsigned int bit3:1;
  unsigned int bit4:1;
  unsigned int bit5:1;
  unsigned int bit6:1;
  unsigned int bit7:1;
} _io_reg; 

typedef enum _BOOL { FALSE = 0, TRUE } BOOL;
#define _BIT(rg,bt) ((volatile _io_reg*)&rg)->bit##bt

//PINA
#define _PINA0	_BIT(PINA,0)
#define _PINA1	_BIT(PINA,1)
#define _PINA2	_BIT(PINA,2)
#define _PINA3	_BIT(PINA,3)
#define _PINA4	_BIT(PINA,4)
#define _PINA5	_BIT(PINA,5)
#define _PINA6	_BIT(PINA,6)
#define _PINA7	_BIT(PINA,7)

#define _PORTA0	_BIT(PORTA,0)
#define _PORTA1	_BIT(PORTA,1)
#define _PORTA2	_BIT(PORTA,2)
#define _PORTA3	_BIT(PORTA,3)
#define _PORTA4	_BIT(PORTA,4)
#define _PORTA5	_BIT(PORTA,5)
#define _PORTA6	_BIT(PORTA,6)
#define _PORTA7	_BIT(PORTA,7)

#define _DDRA0	_BIT(DDRA,0)
#define _DDRA1	_BIT(DDRA,1)
#define _DDRA2	_BIT(DDRA,2)
#define _DDRA3	_BIT(DDRA,3)
#define _DDRA4	_BIT(DDRA,4)
#define _DDRA5	_BIT(DDRA,5)
#define _DDRA6	_BIT(DDRA,6)
#define _DDRA7	_BIT(DDRA,7)
//PINB 
#define _PINB0	_BIT(PINB,0)
#define _PINB1	_BIT(PINB,1)
#define _PINB2	_BIT(PINB,2)
#define _PINB3	_BIT(PINB,3)
#define _PINB4	_BIT(PINB,4)
#define _PINB5	_BIT(PINB,5)
#define _PINB6	_BIT(PINB,6)
#define _PINB7	_BIT(PINB,7)

#define _PORTB0	_BIT(PORTB,0)
#define _PORTB1	_BIT(PORTB,1)
#define _PORTB2	_BIT(PORTB,2)
#define _PORTB3	_BIT(PORTB,3)
#define _PORTB4	_BIT(PORTB,4)
#define _PORTB5	_BIT(PORTB,5)
#define _PORTB6	_BIT(PORTB,6)
#define _PORTB7	_BIT(PORTB,7)

#define _DDRB0	_BIT(DDRB,0)
#define _DDRB1	_BIT(DDRB,1)
#define _DDRB2	_BIT(DDRB,2)
#define _DDRB3	_BIT(DDRB,3)
#define _DDRB4	_BIT(DDRB,4)
#define _DDRB5	_BIT(DDRB,5)
#define _DDRB6	_BIT(DDRB,6)
#define _DDRB7	_BIT(DDRB,7)
//PINC
#define _PINC0	_BIT(PINC,0)
#define _PINC1	_BIT(PINC,1)
#define _PINC2	_BIT(PINC,2)
#define _PINC3	_BIT(PINC,3)
#define _PINC4	_BIT(PINC,4)
#define _PINC5	_BIT(PINC,5)
#define _PINC6	_BIT(PINC,6)
#define _PINC7	_BIT(PINC,7)

#define _PORTC0	_BIT(PORTC,0)
#define _PORTC1	_BIT(PORTC,1)
#define _PORTC2	_BIT(PORTC,2)
#define _PORTC3	_BIT(PORTC,3)
#define _PORTC4	_BIT(PORTC,4)
#define _PORTC5	_BIT(PORTC,5)
#define _PORTC6	_BIT(PORTC,6)
#define _PORTC7	_BIT(PORTC,7)

#define _DDRC0	_BIT(DDRC,0)
#define _DDRC1	_BIT(DDRC,1)
#define _DDRC2	_BIT(DDRC,2)
#define _DDRC3	_BIT(DDRC,3)
#define _DDRC4	_BIT(DDRC,4)
#define _DDRC5	_BIT(DDRC,5)
#define _DDRC6	_BIT(DDRC,6)
#define _DDRC7	_BIT(DDRC,7)
//PIND

#define _PIND0	_BIT(PIND,0)
#define _PIND1	_BIT(PIND,1)
#define _PIND2	_BIT(PIND,2)
#define _PIND3	_BIT(PIND,3)
#define _PIND4	_BIT(PIND,4)
#define _PIND5	_BIT(PIND,5)
#define _PIND6	_BIT(PIND,6)
#define _PIND7	_BIT(PIND,7)

#define _PORTD0	_BIT(PORTD,0)
#define _PORTD1	_BIT(PORTD,1)
#define _PORTD2	_BIT(PORTD,2)
#define _PORTD3	_BIT(PORTD,3)
#define _PORTD4	_BIT(PORTD,4)
#define _PORTD5	_BIT(PORTD,5)
#define _PORTD6	_BIT(PORTD,6)
#define _PORTD7	_BIT(PORTD,7)

#define _DDRD0	_BIT(DDRD,0)
#define _DDRD1	_BIT(DDRD,1)
#define _DDRD2	_BIT(DDRD,2)
#define _DDRD3	_BIT(DDRD,3)
#define _DDRD4	_BIT(DDRD,4)
#define _DDRD5	_BIT(DDRD,5)
#define _DDRD6	_BIT(DDRD,6)
#define _DDRD7	_BIT(DDRD,7)
#endif
