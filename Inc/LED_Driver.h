/*
 * LED_Driver.h
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include "GPIO_Driver.h"

//PG13 is Green, PG14 is Red
#define GREEN_LED 0
#define RED_LED 1

#define GREEN_LED_PORT GPIO_PIN_13
#define RED_LED_PORT GPIO_PIN_14

void LED_Init(uint8_t led);
void LED_EnableClock(uint8_t led);
void LED_Enable(uint8_t led);
void LED_Disable(uint8_t led);
void LED_Toggle(uint8_t led);

#endif /* LED_DRIVER_H_ */
