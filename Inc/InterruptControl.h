/*
 * InterruptControl.h
 *
 *  Created on: Sep 26, 2023
 *      Author: owenallison
 */

#ifndef INTERRUPTCONTROL_H_
#define INTERRUPTCONTROL_H_

#include "STM32F429i.h"

#define EXTI0_IRQ_NUMBER 6
#define TIM2_IRQ_NUMBER 28
#define TIM5_IRQ_NUMBER 50

void InterruptIRQ_Enable(uint8_t IRQ);
void InterruptIRQ_Disable(uint8_t IRQ);
void InterruptIRQ_Clear_Pending(uint8_t IRQ);
void InterruptIRQ_Set_Pending(uint8_t IRQ);

void InterruptIRQ_Configure_Priority(uint8_t IRQ, uint8_t priority);

void EXTI_Clear_Pending(uint8_t pin_num);

#endif