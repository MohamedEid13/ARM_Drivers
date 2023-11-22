/**********************************************************/
/***************** Name    : Mohamed Eid   ******************/
/***************** Date    : 31/7/2021   ******************/
/***************** Version : 1.0         ******************/
/***************** SWC     : STK         ******************/
/**********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

/* Global Pointer to a function */
static void(*STK_Pf)(void) = NULL;
static u8 STK_u8ModeOfInterval;

void STK_voidInit                     (void)
{
	/* Disable Timer and select the CLK Source */
#if STK_u8_CLK_SRC == STK_u8_AHB
	STK->CTRL = 0x00000004;;
#elif STK_u8_CLK_SRC == STK_u8_AHB_8
	STK->CTRL = 0;
#else
	#error"Wrong Choice"
#endif
}

/* Synch function */
u8   STK_u8SetBusyWait         (u32 Copy_u32NumOfTicks)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_u32NumOfTicks <= 0x00FFFFFF)
	{
		Local_u8ErrorState = STD_TYPES_OK;

		/* Load the input value into the LOAD Reg */
		STK->LOAD = Copy_u32NumOfTicks;

		/* Start Timer */
		SET_BIT(STK->CTRL,0);

		/* Wait for the Flag */
		while((GET_BIT(STK->CTRL,16)) == 0);

		/* Disable Timer */
		CLR_BIT(STK->CTRL,0);
		STK->LOAD = 0;
		STK->VAL  = 0;
	}
	return Local_u8ErrorState;
}

/* Async functions */
u8   STK_u8SetIntervalSingle   (u32 Copy_u32NumOfTicks, void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if((Copy_u32NumOfTicks <= 0x00FFFFFF) && (Copy_pf != NULL))
	{
		Local_u8ErrorState = STD_TYPES_OK;
		/* Set Load Register */
		STK->LOAD = Copy_u32NumOfTicks;
		/* Enable Timer */
		SET_BIT(STK->CTRL,0);
		/* Set Callback */
		STK_Pf = Copy_pf;
		/* Set Mode of Interval = Single */
		STK_u8ModeOfInterval = STK_u8_SINGLE_INTERVAL;
		/* Enable Interrupt */
		SET_BIT(STK->CTRL,1);
	}
	return Local_u8ErrorState;
}

u8   STK_u8SetIntervalPeriodic (u32 Copy_u32NumOfTicks, void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if((Copy_u32NumOfTicks <= 0x00FFFFFF) && (Copy_pf != NULL))
	{
		Local_u8ErrorState = STD_TYPES_OK;
		/* Set Load Register */
		STK->LOAD = Copy_u32NumOfTicks - 1;
		/* Enable Timer */
		SET_BIT(STK->CTRL,0);
		/* Set Callback */
		STK_Pf = Copy_pf;
		/* Set Mode of Interval = Periodic */
		STK_u8ModeOfInterval = STK_u8_PERIODIC_INTERVAL;
		/* Enable Interrupt */
		SET_BIT(STK->CTRL,1);
	}
	return Local_u8ErrorState;
}

void STK_voidStopTimer                (void)
{
	CLR_BIT(STK->CTRL,0);
	STK->LOAD = 0;
	STK->VAL  = 0;
}

u8   STK_u8GetElapsedTime      (u32 * Copy_pu32ElapsedTime)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_pu32ElapsedTime != NULL)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		*Copy_pu32ElapsedTime = STK->LOAD - STK->VAL;
	}
	return Local_u8ErrorState;
}

u8   STK_u8GetRemainingTime    (u32 * Copy_pu32RemainingTime)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_pu32RemainingTime != NULL)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		*Copy_pu32RemainingTime = STK->VAL;
	}
	return Local_u8ErrorState;
}

void SysTick_Handler(void)
{
	u8 Local_u8Temp;
	if(STK_u8ModeOfInterval == STK_u8_SINGLE_INTERVAL)
	{
		/* Disable Interrupt */
		CLR_BIT(STK->CTRL,1);

		/* Stop Timer */
		CLR_BIT(STK->CTRL,0);
		STK->LOAD = 0;
		STK->VAL  = 0;
	}
	if(STK_Pf != NULL)
	{
		STK_Pf();
	}
	/* Read Flag to clear it */
	Local_u8Temp = GET_BIT(STK->CTRL,16);
}
