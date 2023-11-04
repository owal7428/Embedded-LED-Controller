/*
 * Button_Driver.h
 *
 *  Created on: Sep 26, 2023
 *      Author: owenallison
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include "GPIO_Driver.h"

#define BUTTON_PORT GPIOA
#define BUTTON_PIN_NUM GPIO_PIN_0

#define BUTTON_PRESSED 1
#define BUTTON_NOT_PRESSED 0

void Button_Init();
void Button_InitInterruptMode();

void Button_EnableClock();

bool Button_IsPressed();

#endif
