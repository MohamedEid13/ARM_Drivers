
/**********************************************************/
/***************** Name    : Mohamed Eid ******************/
/***************** Date    : 31/7/2021   ******************/
/***************** Version : 1.0         ******************/
/***************** SWC     : UART         ******************/
/**********************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/***************************** Interface Macros ************************/
/***interrupt status macro ***/
#define DISABLE_INTERRUPTS         (0x00)
#define ENABLE_TC_INTERRUPT        (0x40)
#define ENABLE_RXNE_INTERRUPT      (0x20)
#define ENABLE_TXC_RXNE_INTERRUPT  (0x60)

/***BaudRate Macros ***/
#define UART_2400_BAUD_RATE           (0xD05) /*((208<<4)|5)*/
#define UART_4800_BAUD_RATE           (0x683)
#define UART_9600_BAUD_RATE           (0x341)
#define UART_115200_BAUD_RATE         (0x45)
/***************************** Function's Prototype ********************/

u8 UART1_u8Init(u8 Copy_u8InterruptStatus,u16 Copy_u16BaudRate);

u8 UART1_u8SendByte(u8 Copy_u8DataByte);

u8 UART1_u8SendByte_Interrupt(u8 Copy_u8DataByte);

/**** Send Stream of data like array for example ****/
u8 UART1_u8SendStream(u8 *Copy_pu8DataByte,u16 Copy_u16DataSize);



u8 UART1_u8ReceiveByte(u8 *Copy_pu8DataByte);

u8 UART1_u8ReceiveByte_Interrupt(u8 *Copy_pu8DataByte);




#endif /* UART_INTERFACE_H_ */
