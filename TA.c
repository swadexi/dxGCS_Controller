#include "all.h"
double j;


int main()
{
init_serial(0);
init_serial(1);
DDRB =0xff;
servo_init();
intro();

sei();
x_est_last = coPilot(0);
x_est_last1= coPilot(1);
kP[ch_rudder] = 10; kD[ch_rudder] = 6;kI[ch_rudder]=1;
kP[ch_elevator]= 150; kD[ch_elevator] = 15;
altx[1] = 200;
		
		while(1)
		{	
			rutin_utama();
		}
}


void rutin_utama()
{
		j++;			
		switcherByRC();	
		
		if(j>=doubleData[0])		
		{		
		sendGround();
		j=0;
		}
}


void sendGround()
{	//dxData[0] = '1'; has been executed at switcher.c
	dxData[1] = coPilot(0);			// ADC IR1
	dxData[2] = coPilot(1);			// ADC IR2
	
	for (i=1;i<29;i++)
	{ dxData[i+2] = buffer_gga[i];}	//Get GGA data From Memory	
	
	for (i=1;i<5;i++)
	{ dxData[i+30]= buffer_rmc[i];}	//Get RMC data From Memory
	
//	dxData[35] = calc_bearing();				//has been executed at calc bearing

	for (i=38;i<=43;i++)
	{ dxData[i] = 3 + servoData[i-36] ; }
	
	 dxData[44] = Volts();			// get volt  and save 
	 dxData[47] = dxCRC();			// count CRC and save 
	
	
	//write(0,0x01);			//Write initial Data (Start of Heading)
	string (0,"dxURO");		//Header
	for (i=0;i<=47;i++)		
	{write(0,dxData[i]);}		
}

void intro()
{
_delay_ms(1000);
write(0,1);
write(0,13);
write(0,10);
string(0,"dxAutoPilot 2012");
write(0,13);
write(0,10);
string(0,"Unila Robotics and Automation");
write(0,13);
write(0,10);
write(0,10);
write(0,10);
_delay_ms(50);
}



