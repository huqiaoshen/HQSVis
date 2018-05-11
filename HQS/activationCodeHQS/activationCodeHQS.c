
#include "activationCodeHQS.h"


activation_t activationCodeAnalyze(uint8 *keyData, uint8 *idData)
{
	activation_t activationData;
	uint8 key[12];
	uint8 id[12];
	uint8 validate = 0;
	for (uint8 i = 0; i < 12; i++)
	{
		*(key + i) = ~(*(keyData + i))^0xA6;
		if (*(key + i) % 2) //ÆæÊý
		{
		  *(key + i) = (*(key + i)) ^ (*(key + i - 1));
		}
		else   //Å¼Êý
		{
			if (i)
				*(key + i) = ~((*(key + i)) ^ (*(key + i - 1)));
			else
				*(key + i) = ~((*(key + i)) ^ 0x45);
		}

		*(id + i) = (*(idData + i)) ^ (*(key + i));

		validate += *(id + i);
	}

	if (validate == *(id + 11))
	{
		activationData.keyCode = TRUE;
	}
	else
	{
		activationData.keyCode = FALSE;
	}

}














