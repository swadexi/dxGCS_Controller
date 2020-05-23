#include "all.h"
int CRC;

uint8_t dxCRC()
{	
	CRC = 0;
	for (i=0;i<=46;i++)
	{CRC = CRC^dxData[i];}
	return CRC;
}

uint8_t servoCRC(uint8_t much)
{
	CRC = 0;
	for (i=2;i<=much;i++)
	{CRC = CRC^storeData[i];}
		if(CRC < 3){CRC = 5;}
	return CRC;
}


uint8_t CRC_WPFLASH(uint8_t much)
{
	CRC = 0;
	for (i=5;i<=much;i++)
	{CRC = CRC^storeData[i];}
	return CRC;


}
