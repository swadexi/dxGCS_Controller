#include "all.h"
#include "dxDef.h"

void switcherByRC()
{
		
	if(_PINA0 == 0 && _PINA1 == 0)
	{
		_delay_ms(3);	
		dxData[0] = '1';
		doubleData[0] = 100;		
	}
	else if(_PINA0 == 1 && _PINA1== 1)
	{	
		Auto_Flight();	
		dxData[0] = '3';
		doubleData[0] = 500;
		altx[1] = altx[0];	
	}
	else if(_PINA0 == 0 && _PINA1 == 1)
	{	
				
		moveServo();
		dxData[0] = '2';
		doubleData[0] = 15000;
	}
	else if(_PINA0 == 1 && _PINA1 == 0)
	{					
		moveServo();
		dxData[0] = '2';
		doubleData[0] = 15000;
	}
}


