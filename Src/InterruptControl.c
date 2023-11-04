/*
 * InterruptControl.c
 *
 *  Created on: Sep 26, 2023
 *      Author: owenallison
 */

#include "InterruptControl.h"

void InterruptIRQ_Enable(uint8_t IRQ)
{
    /*uint8_t shift = IRQ % 32;
    *NVIC_SET_ENABLE |= (1 << shift);*/

    uint8_t regSelect = IRQ / 32;
    uint8_t shift = IRQ % 32;

    *(NVIC_SET_ENABLE + regSelect) &= ~(1 << shift);
    *(NVIC_SET_ENABLE + regSelect) |= (1 << shift);
}

void InterruptIRQ_Disable(uint8_t IRQ)
{
    /*uint8_t shift = IRQ % 32;
    *NVIC_CLEAR_ENABLE |= (1 << shift);*/

    uint8_t regSelect = IRQ / 32;
    uint8_t shift = IRQ % 32;

    *(NVIC_CLEAR_ENABLE + regSelect) &= ~(1 << shift);
    *(NVIC_CLEAR_ENABLE + regSelect) |= (1 << shift);
}

void InterruptIRQ_Clear_Pending(uint8_t IRQ)
{
	/*uint8_t shift = IRQ % 32;
	*NVIC_CLEAR_PENDING |= (1 << shift);*/

    uint8_t regSelect = IRQ / 32;
    uint8_t shift = IRQ % 32;

    *(NVIC_CLEAR_PENDING + regSelect) &= ~(1 << shift);
    *(NVIC_CLEAR_PENDING + regSelect) |= (1 << shift);
}

void InterruptIRQ_Set_Pending(uint8_t IRQ)
{
    /*uint8_t shift = IRQ % 32;
	*NVIC_SET_PENDING |= (1 << shift);*/

    uint8_t regSelect = IRQ / 32;
    uint8_t shift = IRQ % 32;

    *(NVIC_SET_PENDING + regSelect) &= ~(1 << shift);
    *(NVIC_SET_PENDING + regSelect) |= (1 << shift);
}

void InterruptIRQ_Configure_Priority(uint8_t IRQ, uint8_t priority) {
    int regSelect = IRQ/4;
    int bitField = IRQ%4;
    int shift = (IRQ%4)*4;

    uint32_t val = *(NVIC_PRIORITY + regSelect);
    val &= ~(bitField << shift);
    val |= bitField << shift;
}

void EXTI_Clear_Pending(uint8_t pin_num)
{
    EXTI -> PR |= (1 << pin_num);
}
