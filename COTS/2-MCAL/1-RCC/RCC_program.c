/************************************************************/
/***************** Name    : Mohamed Eid   ******************/
/***************** Date    : 31/7/2023    ******************/
/***************** Version : 1.0           ******************/
/***************** SWC     : RCC           ******************/
/************************************************************/
/* LIB Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

/* MCAL */
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"


u8 RCC_u8InitSysClk                      (void)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	/* Enable The Clk to be selected */
	/* Select Clk Source : 1-HSI 2-HSE 3-PLL  */
#if (RCC_u8_CLK_SYS == RCC_u8_HSI)
	RCC->CR   = 0x00000001;
	RCC->CFGR = 0;
#elif (RCC_u8_CLK_SYS == RCC_u8_HSE)
	RCC->CR   = 0x00010000;
	RCC->CFGR = 0x00000001;
#elif (RCC_u8_CLK_SYS == RCC_u8_PLL)
	RCC->CR   = 0x01000000;
	RCC->CFGR = 0x00000002;
#else
	#error"Wrong Choice"
#endif
	return Local_u8ErrorState;
}

u8 RCC_u8EnablePeripheralClk   (u8 Copy_u8BusId,u8 Copy_u8PeripheralId)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8PeripheralId<32)
	{
		switch (Copy_u8BusId)
		{
			case RCC_u8_AHB_BUS :SET_BIT(RCC->AHBENR,Copy_u8PeripheralId);break;
			case RCC_u8_APB1_BUS:SET_BIT(RCC->APB1ENR,Copy_u8PeripheralId);break;
			case RCC_u8_APB2_BUS:SET_BIT(RCC->APB2ENR,Copy_u8PeripheralId);break;
			default: Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

u8 RCC_u8DisablePeripheralClk  (u8 Copy_u8BusId,u8 Copy_u8PeripheralId)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8PeripheralId<32)
	{
		switch (Copy_u8BusId)
		{
			case RCC_u8_AHB_BUS :CLR_BIT(RCC->AHBENR,Copy_u8PeripheralId);break;
			case RCC_u8_APB1_BUS:CLR_BIT(RCC->APB1ENR,Copy_u8PeripheralId);break;
			case RCC_u8_APB2_BUS:CLR_BIT(RCC->APB2ENR,Copy_u8PeripheralId);break;
			default: Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
