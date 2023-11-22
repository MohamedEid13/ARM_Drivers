
/**********************************************************/
/***************** Name    : Mohamed Eid ******************/
/***************** Date    : 31/7/2021   ******************/
/***************** Version : 1.0         ******************/
/***************** SWC     : UART         ******************/
/**********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

/* MCAL */
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"

static u8 Global_TX_CompleteFlag;
static u8 Global_RX_CompleteFlag;


u8 UART1_u8Init(u8 Copy_u8InterruptStatus,u16 Copy_u16BaudRate)
{
	u8 Local_ErrorState=STD_TYPES_OK;

	/* Reset to UART1 CR1& CR2 register */
	UART1->CR1=0;
	UART1->CR2=0;

	/* Enable UART */
	SET_BIT(UART1->CR1,13);

	/* Set interrupt status */
	UART1->CR1 |=Copy_u8InterruptStatus;

	/* Enable TX & RX */
	SET_BIT(UART1->CR1,3);
	SET_BIT(UART1->CR1,2);

	/*Set UART Baud Rate */
	UART1->BRR=Copy_u16BaudRate;

	return Local_ErrorState;
}

u8 UART1_u8SendByte(u8 Copy_u8DataByte)
{
	u8 Local_ErrorState=STD_TYPES_OK;
	/* Checking if the Data Reg is empty or not */
	if(GET_BIT(UART1->SR,7))
	{
		UART1->DR=Copy_u8DataByte;

		/* Waiting the transmission to Complete*/
		while(!GET_BIT(UART1->SR,6));

		/*Clearing TC Flag */
		CLR_BIT(UART1->SR,6);
	}
	else
	{
		Local_ErrorState=STD_TYPES_NOK;
	}
	return Local_ErrorState;
}

u8 UART1_u8SendByte_Interrupt(u8 Copy_u8DataByte)
{
	u8 Local_ErrorState=STD_TYPES_OK;

	if(Global_TX_CompleteFlag)
	{
		UART1->DR=Copy_u8DataByte;
		Global_TX_CompleteFlag=0;
	}
	else
	{
		Local_ErrorState=STD_TYPES_NOK;
	}
	return Local_ErrorState;
}


u8 UART1_u8SendStream(u8 *Copy_pu8DataByte,u16 Copy_u16DataSize)
{
	u8 Local_ErrorState=STD_TYPES_OK;
	while(Copy_u16DataSize--)
	{
			/* Checking if the Data Reg is empty or not */
			if(GET_BIT(UART1->SR,7))
			{
				UART1->DR=*Copy_pu8DataByte;

				/* Waiting the transmission to Complete*/
				while(!GET_BIT(UART1->SR,6));

				/*Clearing TC Flag */
				CLR_BIT(UART1->SR,6);

				/*Increment the data pointer */
				Copy_pu8DataByte++;
			}
			else
			{
				Local_ErrorState=STD_TYPES_NOK;
			}
	}
	return Local_ErrorState;
}



u8 UART1_u8ReceiveByte(u8 *Copy_pu8DataByte)
{
	u8 Local_ErrorState=STD_TYPES_OK;
		/* Checking if the Data Reg is empty or not */
		if(GET_BIT(UART1->SR,5))
		{
			*Copy_pu8DataByte=UART1->DR;

			/*Clearing RXNE Flag */
			CLR_BIT(UART1->SR,5);
		}
		else
		{
			Local_ErrorState=STD_TYPES_NOK;
		}
	return Local_ErrorState;
}

u8 UART1_u8ReceiveByte_Interrupt(u8 *Copy_pu8DataByte)
{
	u8 Local_ErrorState=STD_TYPES_OK;

		if(Global_RX_CompleteFlag)
		{
			*Copy_pu8DataByte=UART1->DR;
			Global_RX_CompleteFlag=0;
		}
		else
		{
			Local_ErrorState=STD_TYPES_NOK;
		}
		return Local_ErrorState;
}


/******************** Handlers *************************/

void USART1_IRQHandler(void)
{
	/*****check if Interrupt due to data transmission ******/
	if(GET_BIT(UART1->SR,6))
	{
		//Data Transmission Complete
		Global_TX_CompleteFlag=1;

		CLR_BIT(UART1->SR,6);
	}
	/*****check if Interrupt due to data Receive ******/
	else if(GET_BIT(UART1->SR,5))
	{
		//Data Receiving Complete
		Global_RX_CompleteFlag=1;

		CLR_BIT(UART1->SR,5);
	}
	else
	{
		/* Do Nothing */
	}
}
