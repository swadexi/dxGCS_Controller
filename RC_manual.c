#include "all.h"
int lastK[8];
int k;

/*@@@@@@@@@@@@@@ dxRCDecoder V1.0 @@@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@ Caution @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*@ Not effective, there are still not expected signal @
  @ Beter using PPM Decoder                            @
  @ I prefer using Multiplexer/selector IC             @*/


void get_signal_and_update()
{
	for(i=0;i<5;i++)
	{
	k =get_signal(i);
	servoData[i] = k;
	k =k*10;
	if (k<900){k=lastK[i];}
	servoSet(i,k);
	lastK[i] = k;	
	}
}


uint16_t get_signal(uint8_t xPin)
{
		loop_until_bit_is_clear(PINB,xPin);
		uint16_t a=0;
		loop_until_bit_is_set(PINB,xPin);
		kk:	
		a++;
		for(uint16_t ur=0; ur<=7; ur++)
		DDRB &=~(1<<xPin);
		if(bit_is_set(PINB,xPin))
		goto kk;		
		return (a+4);	
		


}

