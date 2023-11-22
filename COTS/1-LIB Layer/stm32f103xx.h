/************************************************************/
/***************** Name    : Mohamed Eid   ******************/
/***************** Date    : 31/10/2023    ******************/
/***************** Version : 1.0           ******************/
/***************** SWC     : Target          ******************/
/************************************************************/
#ifndef STM32F103xx_h
#define STM32F103xx_h

/********************** RCC Registers *********************/

#define RCC_u32_BASE_ADDRESS                      0x40021000

typedef struct
{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;
	volatile u32 CSR;
}RCC_RegDef_t;

#define RCC                           ((RCC_RegDef_t*)RCC_u32_BASE_ADDRESS)

/**********************************************************/

/******************************** GPIO Registers **************************************/
#define GPIO_u32_GPIOA_BASE_ADDRESS                       0x40010800U
#define GPIO_u32_GPIOB_BASE_ADDRESS                       0x40010C00U
#define GPIO_u32_GPIOC_BASE_ADDRESS                       0x40011000U 

typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_RegDef_t;

#define GPIOA                          ((GPIO_RegDef_t*)GPIO_u32_GPIOA_BASE_ADDRESS)
#define GPIOB                          ((GPIO_RegDef_t*)GPIO_u32_GPIOB_BASE_ADDRESS)
#define GPIOC                          ((GPIO_RegDef_t*)GPIO_u32_GPIOC_BASE_ADDRESS)


/**************************************************************************************/

/******************************** SYSTICK Registers ***********************************/

#define STK_u32_BASE_ADDRESS                                0xE000E010U

typedef struct
{
	volatile u32 CTRL;
	volatile u32 LOAD;
	volatile u32 VAL;
	volatile u32 CALIB;
}STK_RegDef_t;

#define STK                                  ((STK_RegDef_t*)STK_u32_BASE_ADDRESS)

/**************************************************************************************/

/******************************** NVIC Registers ***********************************/

#define NVIC_u32_BASE_ADDRESS                                0xE000E100U

typedef struct
{
	volatile u32 ISER[32];
	volatile u32 ICER[32];
	volatile u32 ISPR[32];
	volatile u32 ICPR[32];
	volatile u32 IABR[64];
	volatile u32 IPR[9];
}NVIC_RegDef_t;

#define NVIC                                  ((NVIC_RegDef_t*)NVIC_u32_BASE_ADDRESS)
#define SCB_AIRCR                             (*(volatile u32*)(0xE000ED0C))

/**************************************************************************************/

/******************************** EXTI Registers ***********************************/

#define EXTI_u32_BASE_ADDRESS                                0x40010400U

typedef struct
{
	volatile u32 IMR;
	volatile u32 EMR;
	volatile u32 RTSR;
	volatile u32 FTSR;
	volatile u32 SWIER;
	volatile u32 PR;
}EXTI_RegDef_t;

#define EXTI                                  ((EXTI_RegDef_t*)EXTI_u32_BASE_ADDRESS)

/**************************************************************************************/

/******************************** DMA Registers ***********************************/

#define DMA_u32_BASE_ADDRESS                                0x40020000U

typedef struct
{
	volatile u32 ISR;
	volatile u32 IFCR;
	volatile u32 CCR1;
	volatile u32 CNDTR1;
	volatile u32 CPAR1;
	volatile u32 CMAR1;
	volatile u32 reserved1;
	volatile u32 CCR2;
	volatile u32 CNDTR2;
	volatile u32 CPAR2;
	volatile u32 CMAR2;
	volatile u32 reserved2;
	volatile u32 CCR3;
	volatile u32 CNDTR3;
	volatile u32 CPAR3;
	volatile u32 CMAR3;
	volatile u32 reserved3;
	volatile u32 CCR4;
	volatile u32 CNDTR4;
	volatile u32 CPAR4;
	volatile u32 CMAR4;
	volatile u32 reserved4;
	volatile u32 CCR5;
	volatile u32 CNDTR5;
	volatile u32 CPAR5;
	volatile u32 CMAR5;
	volatile u32 reserved5;
	volatile u32 CCR6;
	volatile u32 CNDTR6;
	volatile u32 CPAR6;
	volatile u32 CMAR6;
	volatile u32 reserved6;
	volatile u32 CCR7;
	volatile u32 CNDTR7;
	volatile u32 CPAR7;
	volatile u32 CMAR7;
	volatile u32 reserved7;
}DMA_RegDef_t;

#define DMA                                  ((DMA_RegDef_t*)DMA_u32_BASE_ADDRESS)

/**************************************************************************************/

#endif
