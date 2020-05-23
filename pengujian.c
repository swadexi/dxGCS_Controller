#include "all.h"



void tes_komunikasi()
{	int Data = UDR0;
	ujiCnt++;
	if (ujiCnt	== 36)
	{
		ujiCnt = 0;
		for (i=1;i<=ujiCnt;i++)
		{write (0,WP_DATA[i]);}
	}
	else
	{WP_DATA[ujiCnt] = Data;}
}

