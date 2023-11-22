/**********************************************************/
/***************** Name    : Mohamed Eid  ******************/
/***************** Date    : 31/7/2021   ******************/
/***************** Version : 1.0         ******************/
/***************** SWC     : GPIO        ******************/
/**********************************************************/
/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

/* MCAL */
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

static GPIO_RegDef_t * GPIO_Astr[3] = {GPIOA,GPIOB,GPIOC};

u8 GPIO_u8PinInit           (const GPIO_PinConfig_t * Copy_PstrPinConfig)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8PinMode,Local_u8PinId;
	/* Check if the pointer is wild pointer */
	if(Copy_PstrPinConfig != NULL)
	{
		if((Copy_PstrPinConfig->PortId <= GPIO_u8_GPIOC))
		{
			Local_u8PinMode = Copy_PstrPinConfig->PinMode;
			/* Check if the Mode is Pulled Up */
			if(Local_u8PinMode == GPIO_u8_INPUT_PULL_UP)
			{
				/* Set ODR Register */
				SET_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
				/* Modify Pin Mode */
//				Copy_PstrPinConfig->PinMode &= ~(1<<4);
				Local_u8PinMode &= ~(1<<4);
			}
			else if(Local_u8PinMode == GPIO_u8_INPUT_PULL_DOWN)
			{
				/* CLR ODR Register */
				CLR_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
			}
			/* Set Mode of Pin At 4 bits CRL or CRH */
			if(Copy_PstrPinConfig->PinId <= GPIO_u8_PIN7)
			{
				/* Clear 4 bits */
				GPIO_Astr[Copy_PstrPinConfig->PortId]->CRL &= ((~(0b1111)) << (Copy_PstrPinConfig->PinId * 4));
				/* Set Mode of the PIN */
				GPIO_Astr[Copy_PstrPinConfig->PortId]->CRL |= (Local_u8PinMode << (Copy_PstrPinConfig->PinId * 4));
			}
			else if(Copy_PstrPinConfig->PinId <= GPIO_u8_PIN15)
			{
				Local_u8PinId = Copy_PstrPinConfig->PinId - 8;
				/* Clear 4 bits */
				GPIO_Astr[Copy_PstrPinConfig->PortId]->CRH &= ((~(0b1111)) << (Local_u8PinId * 4));
				/* Set Mode of the PIN */
				GPIO_Astr[Copy_PstrPinConfig->PortId]->CRH |= (Local_u8PinMode << (Local_u8PinId * 4));
			}
			else
			{
				Local_u8ErrorState = STD_TYPES_NOK;
			}
		}
		else
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
					        
u8 GPIO_u8SetPinValue       (const GPIO_PinConfig_t * Copy_PstrPinConfig , u8 Copy_u8PinValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_PstrPinConfig != NULL)
	{
		switch(Copy_u8PinValue)
		{
			case GPIO_u8_HIGH:GPIO_Astr[Copy_PstrPinConfig->PortId]->BSRR = (1<<(Copy_PstrPinConfig->PinId));break;
			case GPIO_u8_LOW :GPIO_Astr[Copy_PstrPinConfig->PortId]->BRR  = (1<<(Copy_PstrPinConfig->PinId));break;
			default : Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
					        
u8 GPIO_u8GetPinValue       (const GPIO_PinConfig_t * Copy_PstrPinConfig , u8 * Copy_Pu8RetunredPinValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((Copy_PstrPinConfig != NULL) && (Copy_Pu8RetunredPinValue != NULL))
	{
		*Copy_Pu8RetunredPinValue = GET_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->IDR,Copy_PstrPinConfig->PinId);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
					        
u8 GPIO_u8TogPinValue       (const GPIO_PinConfig_t * Copy_PstrPinConfig)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_PstrPinConfig != NULL)
	{
		TOG_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
