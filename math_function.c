#include "all.h"
#include <stdlib.h>
char xc[2];
//================= dXPilot Math_Function V.1.0=======
/*=========================== ====== ================*/
#define ToRad(x) (x*3.14)/180.0
#define ToDeg(x) (x*180.0)/M_PI
#define d2r (M_PI / 180.0)

float latx2[3];


void NMEA_koma()
{

 latx[0] = latx[1];
 longx[0] = longx[1];

double degree=(buffer_gga[1]-0x30)*10;
 	  degree +=(buffer_gga[2]-0x30);
double minute=(buffer_gga[3]-0x30)*10;
	  minute +=(buffer_gga[4]-0x30);
	  minute +=(buffer_gga[6]-0x30)*1.0/10;
	  minute +=(buffer_gga[7]-0x30)*1.0/100;
	  minute +=(buffer_gga[8]-0x30)*1.0/1000;
	  minute +=(buffer_gga[9]-0x30)*1.0/10000;	
	  minute = minute*1.00000/ 60;
	  if (buffer_gga[10] == 'S'){i= -1;} else {i=1;}
	 latx[1] = i*(degree + minute);
	
	

 	  degree=(buffer_gga[11]-0x30)*100;
 	  degree +=(buffer_gga[12]-0x30)*10;
	  degree +=(buffer_gga[13]-0x30);
 	  minute=(buffer_gga[14]-0x30)*10;
	  minute +=(buffer_gga[15]-0x30);
	  minute +=(buffer_gga[17]-0x30)*1.0/10;
	  minute +=(buffer_gga[18]-0x30)*1.0/100;
	  minute +=(buffer_gga[19]-0x30)*1.0/1000;
	  minute +=(buffer_gga[20]-0x30)*1.0/10000;	
	  minute = minute*1.00000/ 60;
	  
	  if (buffer_gga[21] == 'W'){i=-1;} else {i=1;}
	 longx[1] = (float) i*(degree + minute);

	// if(latx[0] != latx[1] && longx[0] !=longx[1])
	//  {
	 calc_bearing(latx[0],longx[0],latx[1],longx[1]);
	  //}
	  getAltKoma();
	  

}

void getAltKoma()
{
	if(buffer_gga[25] == '.')
	{	
	altx[0]  = buffer_gga[24]-0x30;
	altx[0] +=(buffer_gga[26]-0x30)*0.1;
	altx[0] +=(buffer_gga[27]-0x30)*0.01;
	altx[0] +=(buffer_gga[28]-0x30)*0.001;
	
	}
	else if(buffer_gga[26] == '.')
	{
	altx[0]  = (buffer_gga[24]-0x30)*10;
	altx[0] +=(buffer_gga[25]-0x30);
	altx[0] +=(buffer_gga[27]-0x30)*0.1;
	altx[0] +=(buffer_gga[28]-0x30)*0.01;
	}	
	else if(buffer_gga[27] == '.')
	{
	altx[0]  = (buffer_gga[24]-0x30)*100;
	altx[0] +=(buffer_gga[25]-0x30)*10;
	altx[0] +=(buffer_gga[26]-0x30)*1;
	altx[0] +=(buffer_gga[28]-0x30)*0.1;
	}
	else if(buffer_gga[28] == '.')
	{ 
	altx[0]  = (buffer_gga[24]-0x30)*1000;
	altx[0] +=(buffer_gga[25]-0x30)*100;
	altx[0] +=(buffer_gga[26]-0x30)*10;
	altx[0] +=(buffer_gga[27]-0x30)*1;
	}
}
/*************************************************************************
 * //Function to calculate the course between two waypoints
 * //movable-type.co.uk
 *************************************************************************/
int calc_bearing(float flat1, float flon1, float flat2, float flon2)
{	float x,y,dLon,dLat,bear_calc;
	int a;
	
	dLat = flat2 - flat1;
	dLon = flon2 - flon1;

	y = sin(dLon) * cos(flat2);
	x = (cos(flat1) * sin(flat2)) - (sin(flat1) * cos(flat2) * cos(dLon));
	bear_calc = fmod(((atan2(y, x)* 180.0 / M_PI) + 360.0),360);
	a= floor(bear_calc);
		
		satuan = (a%10)+0x30;
		puluhan = (a%100)/10;
		puluhan += 0x30;		 
		ratusan = (a % 1000)/100;
		ratusan +=0x30;
		
	dxData[35]=ratusan;
	dxData[36]=puluhan;
	dxData[37]=satuan;
	heading[0] = a;
  return a;
}

int Tbearing(float flat1, float flon1, float flat2, float flon2)
{	float x,y,dLon,dLat,bear_calc;
	int a;
	
	dLat = flat2-flat1;
	dLon = flon2 - flon1;

	y = sin(dLon) * cos(flat2);
	x = (cos(flat1) * sin(flat2)) - (sin(flat1) * cos(flat2) * cos(dLon));
	bear_calc = fmod(((atan2(y, x)* 180.0 / M_PI) + 360.0),360);
	a= floor(bear_calc);		
    return a;
}


//fix distance
float calc_distance(float flat1, float flon1, float flat2, float flon2)
{
 float x = 69.1 * (flat2 - flat1); 
 float y = 69.1 * (flon2 - flon1) * cos(flat1/57.3); 
 return (float)sqrt((float)(x*x) + (float)(y*y))*1609.344; 
}





unsigned char charToHexDigit(char c)
{
  if (c >= 'A')
    return c - 'A' + 10;
  else
    return c - '0';
}

unsigned char stringToByte(char digit1,char digit2)
{
  return charToHexDigit(digit1)*16 + charToHexDigit(digit2);
}








void float_hex(float f)
{
INPUT myfloat;
/*char c; 
c=; 
f= (float) c; */
myfloat.all = f;
}


