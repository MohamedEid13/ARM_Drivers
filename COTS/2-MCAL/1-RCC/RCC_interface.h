/************************************************************/
/***************** Name    : Mohamed Eid   ******************/
/***************** Date    : 31/7/2023    ******************/
/***************** Version : 1.0           ******************/
/***************** SWC     : RCC           ******************/
/************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/* Macros for Buses */
#define RCC_u8_AHB_BUS                      1
#define RCC_u8_APB1_BUS                     2
#define RCC_u8_APB2_BUS                     3

u8 RCC_u8InitSysClk                      (void);

u8 RCC_u8EnablePeripheralClk   (u8 Copy_u8BusId,u8 Copy_u8PeripheralId);

u8 RCC_u8DisablePeripheralClk  (u8 Copy_u8BusId,u8 Copy_u8PeripheralId);


#endif