#include "all.h"
uint8_t CRC,Mode;static bool siap;


void convertToRealNumber(int totalwp)
{
	for(i=0;i<32;i=i+2)
	{eeprom_busy_wait();eeprom_write_byte(i/2,stringToByte(WP_DATA[i],WP_DATA[i+1]));}
	
	for (i=32;i<(totalwp*7)+32;i=i+7)
	{

	  _WP  =(WP_DATA[i]-0x30)*100;
 	  _WP +=(WP_DATA[i+1]-0x30)*10;
	  _WP +=(WP_DATA[i+2]-0x30);
		eeprom_write_word(i,_WP);
	  _WP  =(WP_DATA[i+3]-0x30)*100;
 	  _WP +=(WP_DATA[i+4]-0x30)*10;
	  _WP +=(WP_DATA[i+5]-0x30);
	    eeprom_busy_wait();	
		eeprom_write_word(i+2,_WP);
		eeprom_busy_wait();
     	eeprom_write_byte(i+4,WP_DATA[i+6]);
	}
}

void store_wpData(int char_c)				//Copy Data Waypoint To buffer and EEPROM
{	
		indexWP = 0;
	temp[1] = CRC_WPFLASH(char_c-2);
	if ( temp[1]== storeData[char_c-1])
	{	
	  Jumlah_WP  =(storeData[2]-0x30)*100;
 	  Jumlah_WP +=(storeData[3]-0x30)*10;
	  Jumlah_WP +=(storeData[4]-0x30);
	  eeprom_busy_wait();
	  eeprom_write_byte(18,Jumlah_WP);

			for (i=0;i<=char_c-7;i++)
			{ 
			WP_DATA[i] = storeData[i+5];				
			}
			convertToRealNumber(Jumlah_WP);	
			
	}	
}
//================================dXJOYSTICK MODE Versi V.2===========
//================================ More Efficient ====================
ISR(USART0_RX_vect)
{	
static uint8_t theData,char_count;	
theData = UDR0;
char_count +=1;
if (theData == 0x01){char_count = 0;}				//Data SOH
else if(char_count == 1)
	{Mode = theData;}
else if(theData == 0x02)							//Data STX
	{ 
	if (Mode == 'M'){storeServo(char_count);}							
	else if (Mode == 'A') {store_wpData(char_count);}
	}
else { storeData[char_count] = theData;}		//Get Data and Store them


}

void storeServo(uint8_t sig)
{		
	if (servoCRC(sig-2) == storeData[sig-1])
	{	
		for (i=0;i<sig-2;i++)
		{servoData[i] = storeData [i+2];}		
		siap = true;	
	}
	else
	{	
	siap = false;	
	ascii(0,servoCRC(sig-2),3);
	}
}

void moveServo()
{
	int var;
	if (siap == true)
	{	
		for (int jkl=0;jkl<4;jkl++)
		{						
			var = servoData[jkl]*10;
			servoSet(jkl,var);
		}
	}
}
void exe()
{

static uint8_t theData,char_count;	
theData = UDR0;	
char_count +=1;

if (theData == 0x01){char_count = 0;}				//Data SOH
else if(theData == 0x02)
{storeServo(char_count);}
else { storeData[char_count] = theData;}
}
