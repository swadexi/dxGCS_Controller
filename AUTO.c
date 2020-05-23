#include "all.h"


	//=======    CREATED BY   =============
//========== SWADEXI ISTIQPHARA - dX077========
//======  UNILA ROBOTIKA DAN OTOMASI ===========
//======   UNIVERSITY OF LAMPUNG ================


void get_WP_info()
{	eeprom_busy_wait();
	WP_INFO[LatInfo]  = eeprom_read_float((float *) EE_LAT);
	eeprom_busy_wait();
	WP_INFO[xLatInfo] = eeprom_read_float((float *) EE_xLAT);
	eeprom_busy_wait();
	WP_INFO[LonInfo]  = eeprom_read_float((float *) EE_LON);
	eeprom_busy_wait();
	WP_INFO[xLonInfo] = eeprom_read_float((float *) EE_xLON);
}


void Load_TargetWP(int numWP)
{	get_WP_info();
	numWP = (numWP*7)+32;
	eeprom_busy_wait();
	WP_INFO[5]=(float) WP_INFO[LatInfo] - (eeprom_read_word(numWP)*WP_INFO[xLatInfo]);
	
	dxData[60] = numWP;
	eeprom_busy_wait();
	WP_INFO[6] = WP_INFO[LonInfo] + (eeprom_read_word(numWP+2)*WP_INFO[xLonInfo]);
	eeprom_busy_wait();
	AKSI[0] = eeprom_read_byte((uint8_t *) numWP+4);
}


void Auto_Flight()
{		
		Load_TargetWP(indexWP);
		Tpos target = {WP_INFO[5],WP_INFO[6],AKSI[0]};	
		heading[1] = Tbearing(latx[1],longx[1],target.posLat,target.posLon);
		PID(heading[1],heading[0],ch_rudder);		
		PID(altx[1],altx[0],ch_elevator); 
		doubleData[1] = calc_distance(latx[1],longx[1],target.posLat,target.posLon);	
		if (	doubleData[1] <= 20)
		{	indexWP +=1; 	}
		if (indexWP == eeprom_read_byte(18)){indexWP = 0;}
		dxData[46] =doubleData[1]+10; 
		dxData[45] = indexWP + 48;
}


void PID(int Htarget,int CurH,uint8_t Ch)
{		char xtender=0;	
		if (Ch == ch_rudder)
		{
		if((Htarget - CurH )> 180 || (Htarget - CurH) < -180)
		{	if (CurH > 180) {xtender = 1;}
			else {xtender = -1;}
		}
		else { xtender = 0;}
		}
		else { xtender = 0;}		

		error[Ch] = Htarget - CurH + (xtender*360);	
		P[Ch] = kP[Ch] * error[Ch];
		Xerror[Ch] = error[Ch] - lastError[Ch];
		D[Ch] = kD[Ch] * Xerror[Ch];		
		I[Ch] = kI[Ch] * Xerror[Ch];
		PID_result[Ch] = 1500 -(P[Ch] + D[Ch]+ I[Ch]);

		if(Ch == ch_elevator)
		{
			if (PID_result[Ch] < 1100){PID_result[Ch] = 1100;}
			if (PID_result[Ch] > 1800){PID_result[Ch] = 1800;}
		}
		else
		{
			if (PID_result[Ch] < 1000){PID_result[Ch] = 1000;}
			if (PID_result[Ch] > 2000){PID_result[Ch] = 2000;}
		}
		servoData[Ch] = PID_result[Ch];				
		servoSet(Ch,PID_result[Ch]);		//1500
		lastError[Ch] = error[Ch];	
}


