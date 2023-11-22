/**********************************************************/
/***************** Name    : Mohamed Eid  ******************/
/***************** Date    : 31/7/2021   ******************/
/***************** Version : 1.0         ******************/
/***************** SWC     : STK         ******************/
/**********************************************************/
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

void STK_voidInit                     (void);

/* Synch function */
u8   STK_u8SetBusyWait         (u32 Copy_u32NumOfTicks);

/* Async functions */
u8   STK_u8SetIntervalSingle   (u32 Copy_u32NumOfTicks, void(*Copy_pf)(void));

u8   STK_u8SetIntervalPeriodic (u32 Copy_u32NumOfTicks, void(*Copy_pf)(void));

void STK_voidStopTimer                (void)           ;

u8   STK_u8GetElapsedTime      (u32 * Copy_pu32ElapsedTime);

u8   STK_u8GetRemainingTime    (u32 * Copy_pu32RemainingTime);

#endif
