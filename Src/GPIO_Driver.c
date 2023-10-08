/*
 * GPIO_Driver.c
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#include "GPIO_Driver.h"

void GPIO_Init(GPIO_Handle_t* handle) {

	uint8_t pin_num = handle -> GPIO_PinConfig.PinNumber;
	
	// Configure the port mode register
	uint32_t temp = handle -> GPIO_PinConfig.PinMode << (pin_num * 2);
	handle -> pGPIOx -> MODER &= ~(0x3 << (2 * pin_num));
	handle -> pGPIOx -> MODER |= temp;

	uint8_t interruptMode = handle -> GPIO_PinConfig.PinInterruptMode;

	if (interruptMode != NO_INTERRUPT_SELECTED) {
		if (interruptMode == FALLING_EDGE_INTERRUPT) {
			EXTI -> FTSR |= (1 << pin_num);
			EXTI -> RTSR &= ~(1 << pin_num);
		}
		else if (interruptMode == RISING_EDGE_INTERRUPT) {
			EXTI -> FTSR &= ~(1 << pin_num);
			EXTI -> RTSR |= (1 << pin_num);
		}
		else if (interruptMode == FALLING_AND_RISING_INTERRUPT) {
			EXTI -> FTSR |= (1 << pin_num);
			EXTI -> RTSR |= (1 << pin_num);
		}

		uint8_t regSelect = pin_num/4;
		uint8_t pin_loc = pin_num % 4;
		uint16_t portCode = GPIO_ReturnPortCode(handle ->pGPIOx);
		
		SYSCFG_CLOCK_ENABLE;

		SYSCFG -> EXTICR[regSelect] |= (portCode << (pin_loc * 4));
		EXTI -> IMR |= (1 << pin_num);
	}

	// Configure the output speed register
	temp = handle -> GPIO_PinConfig.PinSpeed << (pin_num * 2);
	handle -> pGPIOx -> OSPEEDR &= ~(0x3 << (2 * pin_num));
	handle -> pGPIOx -> OSPEEDR |= temp;

	// Configure the pull-up/pull-down register
	temp = handle -> GPIO_PinConfig.PinPuPdControl << (pin_num * 2);
	handle -> pGPIOx -> PUPDR &= ~(0x3 << (2 * pin_num));
	handle -> pGPIOx -> PUPDR |= temp;

	// Configure the output type register
	temp = handle -> GPIO_PinConfig.OPType << (pin_num);
	handle -> pGPIOx -> OTYPER &= ~(0x1 << (pin_num));
	handle -> pGPIOx -> OTYPER |= temp;

	/* Check if pin mode is set to alt fun
	If yes, then configure */
	if (handle -> GPIO_PinConfig.PinMode == PIN_MODE_CONFIG_ALTFUN) {
		uint32_t altfun_reg = pin_num / 8;
		uint32_t pin_loc = pin_num % 8;

		temp = handle -> GPIO_PinConfig.PinAltFunMode << (pin_loc * 4);
		handle -> pGPIOx -> AFR[altfun_reg] &= ~(0x7 << (pin_loc * 4));
		handle -> pGPIOx -> AFR[altfun_reg] |= temp;
	}
}
void GPIO_ClockEnableOrDisable(GPIO_RegDef_t* reg, uint8_t enableOrDisable) {
	
	if (reg == GPIOA) {
		if (enableOrDisable == ENABLE)
			GPIOx_CLOCK_ENABLE(GPIOA_OFFSET);

		else if (enableOrDisable == DISABLE)
			GPIOx_CLOCK_DISABLE(GPIOA_OFFSET);
	}
	else if (reg == GPIOG) {
		if (enableOrDisable == ENABLE)
			GPIOx_CLOCK_ENABLE(GPIOG_OFFSET);

		else if (enableOrDisable == DISABLE)
			GPIOx_CLOCK_DISABLE(GPIOG_OFFSET);
	}
}
void GPIO_Toggle(GPIO_RegDef_t* reg, uint8_t pin_num) {
	
	reg -> ODR ^= 1 << pin_num;
}

void GPIO_Write(GPIO_RegDef_t* reg, uint8_t pin_num, uint8_t val) {
	
	if (val == 1) {
		reg -> ODR |= 1 << pin_num;
	} 
	else {
		reg -> ODR &= ~(1 << pin_num);
	}
}

uint8_t GPIO_ReadFromPin(GPIO_RegDef_t* reg, uint8_t pin_num) {
	return (uint8_t) ((reg -> IDR >> pin_num) & 0x01);
}

uint16_t GPIO_ReturnPortCode(GPIO_RegDef_t* reg) {
	if (reg == GPIOA)
		return 0x0000;
	else
		return 0;
}

void GPIO_EnableOrDisableInterrupt(uint8_t IRQ, uint8_t enableOrDisable) {
	if (enableOrDisable == ENABLE) {
		InterruptIRQ_enable(IRQ);
	}
	else if (enableOrDisable == DISABLE) {
		InterruptIRQ_disable(IRQ);
	}
}
