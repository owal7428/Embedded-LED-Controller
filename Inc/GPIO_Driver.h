/*
 * GPIO_Driver.h
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include "STM32F429i.h"
#include "InterruptControl.h"

#define GPIO_PIN_0 0
#define GPIO_PIN_1 1
#define GPIO_PIN_2 2
#define GPIO_PIN_3 3
#define GPIO_PIN_4 4
#define GPIO_PIN_5 5
#define GPIO_PIN_6 6
#define GPIO_PIN_7 7
#define GPIO_PIN_8 8
#define GPIO_PIN_9 9
#define GPIO_PIN_10 10
#define GPIO_PIN_11 11
#define GPIO_PIN_12 12
#define GPIO_PIN_13 13
#define GPIO_PIN_14 14
#define GPIO_PIN_15 15

#define PIN_MODE_CONFIG_GPIN 0
#define PIN_MODE_CONFIG_GPOUT 1
#define PIN_MODE_CONFIG_ALTFUN 2
#define PIN_MODE_CONFIG_ANALOG 3

#define OPTYPE_PUSH_PULL 0
#define OPTYPE_OPEN_DRAIN 1

#define OSPEED_LOW 0
#define OSPEED_MED 1
#define OSPEED_HIGH 2
#define OSPEED_VHIGH 3

#define PUPD_CONTROL_NONE 0
#define PUPD_CONTROL_PU 1
#define PUPD_CONTROL_PD 2
#define PUPD_CONTROL_RESERVED 3

#define NO_INTERRUPT_SELECTED 0
#define FALLING_EDGE_INTERRUPT 1
#define RISING_EDGE_INTERRUPT 2
#define FALLING_AND_RISING_INTERRUPT 3

#define GPIOA_PORT_NUMBER 0
#define GPIOG_PORT_NUMBER 6

typedef struct
{
	uint8_t PinNumber;		// Pin Number
	uint8_t PinMode;		// Pin Mode
	uint8_t OPType;			// Output Type
	uint8_t PinSpeed;		// Pin Speed
	uint8_t PinPuPdControl; // Pin Push up/ Pull Down Control
	uint8_t PinAltFunMode; 	// Alternate Function mode
	uint8_t PinInterruptMode;

} GPIO_PinConfig_t;

typedef struct
{
	GPIO_RegDef_t* pGPIOx; // GPIO port
	GPIO_PinConfig_t GPIO_PinConfig; // The pin configurations

} GPIO_Handle_t;

void GPIO_Init(GPIO_Handle_t* handle);
void GPIO_ClockEnableOrDisable(GPIO_RegDef_t* reg, uint8_t enableOrDisable);

void GPIO_Toggle(GPIO_RegDef_t* reg, uint8_t pin_num);
void GPIO_Write(GPIO_RegDef_t* reg, uint8_t pin_num, uint8_t val);

uint8_t GPIO_ReadFromPin(GPIO_RegDef_t* reg, uint8_t pin_num);

uint16_t GPIO_ReturnPortCode(GPIO_RegDef_t* reg);
uint16_t GPIO_ReturnPortNumber(GPIO_RegDef_t* reg);

void GPIO_EnableOrDisableInterrupt(uint8_t IRQ, uint8_t enableOrDisable);

#endif /* GPIO_DRIVER_H_ */
