/*
 * ApplicationCode.h
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#ifndef APPLICATIONCODE_H_
#define APPLICATIONCODE_H_

#include "LED_Driver.h"
#include "Button_Driver.h"
#include "Scheduler.h"

#define NAME_LENGTH 11
#define MAGNIFY 250000

#define BUTTON_INTERRUPT_ENABLE 1

void ApplicationInit();

void InitGreenLED();
void InitRedLED();
void InitRedGreenLEDs();

void ToggleGreenLED();
void ToggleRedLED();

void EnableGreenLED();
void EnableRedLED();

void DisableGreenLED();
void DisableRedLED();

void InitButton();
void InitButtonInterruptMode();
void ButtonPollingRoutine();

void Delay(uint32_t delay);


#endif /* APPLICATIONCODE_H_ */
