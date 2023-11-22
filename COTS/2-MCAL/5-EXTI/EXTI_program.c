/**********************************************************/
/***************** Name    : Mohamed Eid ******************/
/***************** Date    : 31/7/2021   ******************/
/***************** Version : 1.0         ******************/
/***************** SWC     : EXTI         ******************/
/**********************************************************/
/**************************************** Includes ****************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "stm32f103xx.h"
#include "EXTI_private.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"

/**************************************** Important typedefs ****************************************/

typedef void(*fptr)(void);

/**************************************** Important variables ****************************************/

static fptr Global_pfArray[7] = {NULL, NULL, NULL, NULL, NULL,
								 NULL, NULL};

/**************************************** Functions' definitions ****************************************/

u8 EXTI_u8SetInterruptStatus(u8 Copy_u8EXTINumber, u8 Copy_u8EXTIStatus)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	switch(Copy_u8EXTIStatus)
	{
		case EXTI_INTERRUPT_NOT_MASKED:

			Local_u8ErrorState = STD_TYPES_OK;
			SET_BIT(EXTI -> IMR, Copy_u8EXTINumber);
			break;

		case EXTI_INTERRUPT_MASKED:

			Local_u8ErrorState = STD_TYPES_OK;
			CLR_BIT(EXTI -> IMR, Copy_u8EXTINumber);
			break;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8SetInterruptEdge(u8 Copy_u8EXTINumber, u8 Copy_u8EXTIEdge)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	switch(Copy_u8EXTIEdge)
	{
		case EXTI_RISING_EDGE:

			Local_u8ErrorState = STD_TYPES_OK;
			SET_BIT(EXTI -> RTSR, Copy_u8EXTINumber);
			break;

		case EXTI_FALLING_EDGE:

			Local_u8ErrorState = STD_TYPES_OK;
			SET_BIT(EXTI -> FTSR, Copy_u8EXTINumber);
			break;

		case EXTI_RISING_FALLING_EDGE:

			Local_u8ErrorState = STD_TYPES_OK;
			SET_BIT(EXTI -> RTSR, Copy_u8EXTINumber);
			SET_BIT(EXTI -> FTSR, Copy_u8EXTINumber);
			break;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8ClearInterruptPending(u8 Copy_u8EXTINumber)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	SET_BIT(EXTI -> PR, Copy_u8EXTINumber);

	return Local_u8ErrorState;
}

u8 EXTI_u8IsInterruptActive(u8 Copy_u8EXTINumber, u8* Copy_pu8EXTIStatus)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	*Copy_pu8EXTIStatus = GET_BIT(EXTI -> PR, Copy_u8EXTINumber);

	return Local_u8ErrorState;
}

u8 EXTI_u8SetInterruptCallback(u8 Copy_u8EXTINumber, void (*Copy_pfCallback)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8EXTINumber > 4 && Copy_u8EXTINumber < 10)
	{
		Copy_u8EXTINumber = 5;
	}
	else if(Copy_u8EXTINumber >= 10 && Copy_u8EXTINumber <= 15)
	{
		Copy_u8EXTINumber = 6;
	}
	else
	{
		/*Do nothing*/
	}

	Global_pfArray[Copy_u8EXTINumber] = Copy_pfCallback;

	return Local_u8ErrorState;
}

/**************************************** EXTI ISRs ****************************************/

void EXTI0_IRQHandler(void)
{
	SET_BIT(EXTI -> PR, 0);

	if(Global_pfArray[EXTI_LINE0] != NULL)
	{
		Global_pfArray[EXTI_LINE0]();
	}
	else
	{
		/*Do nothing*/
	}
}

void EXTI1_IRQHandler(void)
{
	SET_BIT(EXTI -> PR, 1);

	if(Global_pfArray[EXTI_LINE1] != NULL)
	{
		Global_pfArray[EXTI_LINE1]();
	}
	else
	{
		/*Do nothing*/
	}
}

void EXTI2_IRQHandler(void)
{
	SET_BIT(EXTI -> PR, 2);

	if(Global_pfArray[EXTI_LINE2] != NULL)
	{
		Global_pfArray[EXTI_LINE2]();
	}
	else
	{
		/*Do nothing*/
	}
}

void EXTI3_IRQHandler(void)
{
	SET_BIT(EXTI -> PR, 3);

	if(Global_pfArray[EXTI_LINE3] != NULL)
	{
		Global_pfArray[EXTI_LINE3]();
	}
	else
	{
		/*Do nothing*/
	}
}

void EXTI4_IRQHandler(void)
{
	SET_BIT(EXTI -> PR, 4);

	if(Global_pfArray[EXTI_LINE4] != NULL)
	{
		Global_pfArray[EXTI_LINE4]();
	}
	else
	{
		/*Do nothing*/
	}
}

void EXTI9_5_IRQHandler(void)
{
	EXTI -> PR |= (0b11111 << 5);

	if(Global_pfArray[EXTI_LINE5_9] != NULL)
	{
		Global_pfArray[EXTI_LINE5_9]();
	}
	else
	{
		/*Do nothing*/
	}
}

void EXTI15_10_IRQHandler(void)
{
	EXTI -> PR |= (0b111111 << 10);

	if(Global_pfArray[EXTI_LINE10_15] != NULL)
	{
		Global_pfArray[EXTI_LINE10_15]();
	}
	else
	{
		/*Do nothing*/
	}
}
