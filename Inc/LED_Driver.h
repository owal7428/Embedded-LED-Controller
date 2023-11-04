/*
 * LED_Driver.h
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include "GPIO_Driver.h"
#include "Timer_Driver.h"

//PG13 is Green, PG14 is Red
#define GREEN_LED 0
#define RED_LED 1

#define GREEN_LED_PORT GPIO_PIN_13
#define RED_LED_PORT GPIO_PIN_14

#define TIM2_DEFAULT_PRIORITY 35
#define TIM5_DEFAULT_PRIORITY 57
#define TIM_ELEVATED_PRIORITY 15

void LED_Init(uint8_t led);
void LED_EnableClock(uint8_t led);
void LED_Enable(uint8_t led);
void LED_Disable(uint8_t led);
void LED_Toggle(uint8_t led);

void LED_Timer2_Init();
void LED_Timer2_Start();
void LED_Timer2_Stop();
void LED_Timer2_Reset();
void LED_Timer2_Priority();
void LED_Timer2_Priority_Reset();

void LED_Timer5_Init();
void LED_Timer5_Start();
void LED_Timer5_Stop();
void LED_Timer5_Reset();
void LED_Timer5_Priority();
void LED_Timer5_Priority_Reset();

#endif /* LED_DRIVER_H_ */
