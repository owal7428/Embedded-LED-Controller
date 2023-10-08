/*
 * STM32F429i.h
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#ifndef STM32F429I_H_
#define STM32F429I_H_

#include "stdint.h"
#include "stdbool.h"

#define ACTIVE 1
#define NON_ACTIVE 0
#define SET 1
#define RESET 0
#define ENABLE SET
#define DISABLE RESET

// The following memory addresses are defined in maunal for STM32f4-discorvery

#define PERIPHERAL_BASE_ADDR 0x40000000u

// Bus memory addresses

#define APB2_BASE_ADDR 		(PERIPHERAL_BASE_ADDR + 0X13800)
#define AHB1_BASE_ADDR 		(PERIPHERAL_BASE_ADDR + 0x20000)

// Port memory addresses

#define SYSCFG_BASE_ADDR	(APB2_BASE_ADDR + 0x0)
#define EXTI_BASE_ADDR 		(APB2_BASE_ADDR + 0x400)

#define GPIOA_BASE_ADDR 	(AHB1_BASE_ADDR + 0x0)
#define GPIOG_BASE_ADDR 	(AHB1_BASE_ADDR + 0x1800)
#define RCC_BASE_ADDR 		(AHB1_BASE_ADDR + 0x3800)

// Nested Vectored Interrupt Controller

#define NVIC_ISER0 ((volatile uint32_t*) 0xE000e100)
#define NVIC_ICER0 ((volatile uint32_t*) 0xE000e180)
#define NVIC_ISPR0 ((volatile uint32_t*) 0xE000e200)
#define NVIC_ICPR0 ((volatile uint32_t*) 0xE000e280)

#define NVIC_SET_ENABLE 	NVIC_ISER0
#define NVIC_CLEAR_ENABLE 	NVIC_ICER0
#define NVIC_SET_PENDING	NVIC_ISPR0
#define NVIC_CLEAR_PENDING	NVIC_ICPR0

typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	volatile uint32_t CMPCR;

} SYSCFG_RegDef_t;

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
} EXTI_RegDef_t;

typedef struct
{
	volatile uint32_t MODER;	//offset 0x00
	volatile uint32_t OTYPER;	//offset 0x04
	volatile uint32_t OSPEEDR;	//offset 0x08
	volatile uint32_t PUPDR;	//...
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];

} GPIO_RegDef_t;

typedef struct
{
	volatile uint32_t CR;			//offset 0x00
	volatile uint32_t PLLCFGR;		//offset 0x04
	volatile uint32_t CFGR;			//offset 0x08
	volatile uint32_t CIR;			//...
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	volatile uint32_t reserved1;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t reserved2[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	volatile uint32_t reserved3;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t reserved4[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	volatile uint32_t reserved5;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t reserved6[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t reserved7[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t PLLSAICFGR;
	volatile uint32_t DCKCFGR;

} RCC_RegDef_t;

// Casting memory allocated for registers to struct of same size

#define SYSCFG ((SYSCFG_RegDef_t*) SYSCFG_BASE_ADDR)
#define EXTI ((EXTI_RegDef_t*) EXTI_BASE_ADDR)

#define GPIOA ((GPIO_RegDef_t*) GPIOA_BASE_ADDR)
#define GPIOG ((GPIO_RegDef_t*) GPIOG_BASE_ADDR)
#define RCC ((RCC_RegDef_t*) RCC_BASE_ADDR)


#define GPIOA_OFFSET 0
#define GPIOG_OFFSET 6

#define SYSCFG_CLOCK_ENABLE (RCC -> APB2ENR |= (1 << 14))
#define SYSCFG_CLOCK_DISABLE (RCC -> APB2ENR &= ~(1 << 14))

#define GPIOx_CLOCK_ENABLE(x) (RCC -> AHB1ENR |= (1 << x))
#define GPIOx_CLOCK_DISABLE(x) (RCC -> AHB1ENR &= ~(1 << x))

#endif /* STM32F429I_H_ */
