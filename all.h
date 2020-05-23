#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h> 
#include "initvoid.h"
#include "servo.h"
#include "eeprom_addr.h"

#define speed		1
#define latitude	1
#define longitude	2
#define	Home		0

#define ch_aileron		0
#define ch_elevator		1
#define ch_throtle		2
#define ch_rudder		3	



int indexWP;
uint16_t time;
char buffer[255];

#define TRUE	1
#define FALSE	0
int i,ujiCnt;
int data[7];
unsigned char EEPROM_read(unsigned int uiAddress);
uint8_t last,last2,last3;


unsigned char var;


//========================GPS
uint8_t satuan1, satuan, puluhan, ratusan,ribuan;

char gps_string[42];
float cur_latitude;		// degree
float cur_longitude;	// degree
uint16_t cur_altitude;	// meter
uint16_t cur_heading;	// degree
uint8_t	cur_speed;		// m/s
uint8_t satelit_used;	// number satelit used
char data_valid;		// A = available, V = void
char long_UTM;			// longitude UTM W/E
char buffer_rmc[10];	//buffer for GPRMC
char buffer_gga[40];		//buffer for GPGGA
//static bool transmitMode;
char flightMode;
char AKSI[1];
float xdxData ;

uint8_t dxData[70];
uint8_t storeData[750];
uint16_t coPilot(uint8_t mux);
uint8_t Volts();
double doubleData[2];
int Jumlah_WP;
int temp[1];
int WP_DATA[700];
#define LED_PORT	PORTC
#define GPS_LED		6
#define Auto_LED	5
#define Manual_LED	4
int _WP;
int heading[3];
uint16_t cHx;


typedef struct 
{ 
char BYTE0; 
char BYTE1; 
char BYTE2; 
char BYTE3; 
}BYTES; 

typedef union 
{ 
float all; 
BYTES bytes; 
}INPUT; 

typedef struct
{ 
float posLat; 
float posLon;
char aksi;
}Tpos; 

//======Kalman Filter ========
	float x_est,x_est1,x_est_last1,x_est_last;




int error[4],Xerror[4],lastError[4],kP[4],kD[4],kI[4],P[4],D[4],I[4],PID_result[4];
int getALTITUDE[1];
void rutin_utama();
