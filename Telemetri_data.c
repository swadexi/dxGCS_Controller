#include "all.h"
uint8_t j,gga=0, rmc=0;


	float x_est_last = 0,x_est_last1 = 0;
    float P_last = 0,P_last1 = 0;
    //the noise in the system
    float Q = 0.022;
    float R = 0.617;
    
    float K,K1;
    float Pk,Pk1;
    float P_temp,P_temp1;
    float x_temp_est,x_temp_est1;
    
    float z_measured,z_measured1; //the 'noisy' value we measured
    float z_real,z_real1; //the ideal value we wish to measure

ISR(USART1_RX_vect)
{	
get_gps();
}

void parsing_gga()
{
	
	for (i=1;i<29;i++)
	{
		write(0,buffer_gga[i]);		
	}
	
	

}

void parsing_rmc()
{
	for (i=1;i<5;i++)
	{
		write(0,buffer_rmc[i]);
		
	}
}

void cekDataGPS()
{

}

// @ GPS DATA USING INTERUPT : IMAN DP.2007			@

void get_gps()
{

static uint8_t char_count,koma,index1, index2;//,char_data ;
static uint8_t wait = 0, wait_rmc=0, wait_gga=0;
	
	// get incoming data from UDR
	char char_data = UDR1;
	// increment char_count
	char_count++;
    //	write(UDR1);
	//  wait for',' to save data
	if(char_data == ',')
	{
		//write(char_data);
		koma++;
	}

	//wait for '$' and data GGA or RMC
	else if(!wait)
	{
		if(char_data == '$')
		{	
			// restart counting
			char_count = 1;
			// clear koma dan index
			koma 		= FALSE;
			index1 		= FALSE;
			index2		= FALSE;	
			
		}
		
		// check G in GGA on fifth incoming character 
		// wait_gga complete, then get data GPS
		else if(char_count ==  5 && char_data == 'G')
		{	
			wait_gga	=	TRUE;
			wait 		= 	TRUE;
			gga			=	FALSE;
		//	write(0x20);
		}

		// wait_rmc complete, then get data GPS
		else if(char_count ==  6 && char_data == 'C')
		{	
			wait_rmc	=	TRUE;
			wait 		=	TRUE;//TRU1;//E
			rmc			=	FALSE;//write(0x20);
		}


	}
	else
	{	
		//cek for data GPGGA,if yes get it
		if(wait_gga==1)
		{	LED_PORT |=_BV(GPS_LED);
			//cek for data 0x0a(enter),end of data
			if(char_data == 0x0A)
			{
					wait_gga 	= 	FALSE;
					wait		=	FALSE;
					gga			=	TRUE;	//satu berarti sudah bisa diambil datanya
			NMEA_koma();
			}
			else
			{
				switch(koma)
				{
					
				    case 2:
					case 3:
					case 4:
					case 5:
					case 7:
					case 9:	//				//GGA: ALTITUDE(3karakter)	
					goto store_data1;											store_data1:
					{			
					index1++;					
					buffer_gga[index1]=char_data;					
				//	write(char_data);
				
					}
				}
			}
		}	
	
			
		
		//cek for data GPRMC,if yes get it
		else if(wait_rmc==1)
		{
			//cek for data 0x0a(enter),end of data
			if(char_data == 0x0A)
			{
				
				wait_rmc 	= FALSE	;
				wait		= FALSE;
				rmc			= TRUE;	//satu berarti rmc sudah bisa diambil datanya
			NMEA_koma(); 
			}
			// save to buffer
			else			
			{
					
				switch(koma)
				{			
					//case 2:	
			    	//case 3:			//RMC: LATITUDE					
			      	//case 4:			//RMC: MATA ANGIN N ATAU S	
					//case 5:			//RMC: LONGITUDE	
				    //case 6:			//RMC: MATA ANGIN E ATAU W, GGA: FIX QUALITY				
				    //case 1:
				    case 7:			//RMC: SPEED FROM GROUND, GGA: NUMBER OF SATELITE				
				    //case 8:			//RMC: COURSE
					goto store_data2;
					store_data2:
					{
						index2++;
				//		buffer_rmc[index2]=char_data;			

					}
				
				}
				
			}
		}
		
	}



}

uint16_t coPilot(uint8_t mux)
{ 
	if (mux == 1){
	ADMUX = 0b01000010;
	ADCSRA= 0x84;							// set ADCSRA dengan nilai prescaller 16
	ADCSRA |=(1<<ADSC);						// start konversi ADC
	loop_until_bit_is_set(ADCSRA, ADIF);	// pantau nilai ADIF
	ADCSRA |=(1<<ADIF);		
	cHx = (ADCW/4) ;
	x_temp_est1 = x_est_last1;
    P_temp1 = P_last1 + Q;
        //calculate the Kalman gain
    K1 = P_temp1 * (1.0/(P_temp1 + R));
        //measure
    z_measured1 = cHx; //the real measurement plus noise
        //correct
    x_est1 = x_temp_est1 + K1 * (z_measured1 - x_temp_est1); 
    Pk = (1- K) * P_temp;
	
		P_last1 = Pk1;
        x_est_last1 = x_est1;
		cHx = cHx;
	
	}	
	else if (mux == 0)
	{
	ADMUX = 0b01000011;
	ADCSRA= 0x84;							// set ADCSRA dengan nilai prescaller 16
	ADCSRA |=(1<<ADSC);						// start konversi ADC
	loop_until_bit_is_set(ADCSRA, ADIF);	// pantau nilai ADIF
	ADCSRA |=(1<<ADIF);		
	cHx = (ADCW/4) ;	
	 
	 x_temp_est = x_est_last;
     P_temp = P_last + Q;
        //calculate the Kalman gain
     K = P_temp * (1.0/(P_temp + R));
        //measure
     z_measured = cHx; //the real measurement plus noise
        //correct
     x_est = x_temp_est + K * (z_measured - x_temp_est); 
     Pk = (1- K) * P_temp;
	
		P_last = Pk;
        x_est_last = x_est;
		cHx = cHx;
	}

return cHx;
}


uint8_t Volts()
{
		ADMUX= 0b01000100;			// inisialisasi ADC 0
		ADCSRA= 0x84;				// set ADCSRA dengan nilai prescaller 16
		ADCSRA |=(1<<ADSC);						// start konversi ADC
		loop_until_bit_is_set(ADCSRA, ADIF);	// pantau nilai ADIF
		ADCSRA |=(1<<ADIF);		
		return ADCW/4;
}

