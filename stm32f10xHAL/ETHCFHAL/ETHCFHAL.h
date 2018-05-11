
#ifndef _ETHCFHAL_h
#define _ETHCFHAL_h
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32_eth.h"


#include "HQSlwip.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DP83848_PHY        /* Ethernet pins mapped on STM3210C-EVAL Board */
#define PHY_ADDRESS       0x01 /* Relative to STM3210C-EVAL Board */

//#define MII_MODE        /* MII mode for STM3210C-EVAL Board (MB784) (check jumpers setting) */
#define RMII_MODE         /* RMII mode for STM3210C-EVAL Board (MB784) (check jumpers setting) */



/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void ETHCFHAL_Iint(void);

void ETH_LinkScan(void);

#endif



