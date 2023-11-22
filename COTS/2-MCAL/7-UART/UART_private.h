/**********************************************************/
/***************** Name    : Mohamed Eid ******************/
/***************** Date    : 31/7/2021   ******************/
/***************** Version : 1.0         ******************/
/***************** SWC     : UART         ******************/
/**********************************************************/

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/******************************** USART1 Registers ***********************************/

#define UART1_u32_BASE_ADDRESS                                0x40013800U

typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}UART1_RegDef_t;

#define UART1                                  ((UART1_RegDef_t*)UART1_u32_BASE_ADDRESS)

/**************************************************************************************/

/******************************** USART2 Registers ***********************************/

#define UART2_u32_BASE_ADDRESS                                0x40004400U

typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}UART2_RegDef_t;

#define UART2                                  ((UART2_RegDef_t*)UART2_u32_BASE_ADDRESS)

/**************************************************************************************/

#endif /* UART_PRIVATE_H_ */
