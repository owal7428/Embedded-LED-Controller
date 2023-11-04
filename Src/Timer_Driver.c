/*
 * Timer_Driver.c
 *
 *  Created on: Oct 10, 2023
 *      Author: owenallison
 */

#include "Timer_Driver.h"

void Timer_Init(Timer_Handle_t* handle) {
    uint32_t temp = handle -> timerConfig.autoReloadValue;
    handle -> timer -> ARR &= ~(0xFFFF << 16);
    handle -> timer -> ARR |= temp << 16;

    temp = handle -> timerConfig.masterModeSelection;
    handle -> timer -> CR2 &= ~(0x7 << 4);
    handle -> timer -> CR2 |= temp << 4;

    temp = handle -> timerConfig.clockDivisionValue;
    handle -> timer -> CR1 &= ~(0x3 << 8);
    handle -> timer -> CR1 |= temp << 8;

    temp = handle -> timerConfig.prescalerValue;
    handle -> timer -> SMCR &= ~(0x3 << 12);
    handle -> timer -> SMCR |= temp << 12;

    temp = handle -> timerConfig.centerAlignedModeSelect;
    handle -> timer -> CR1 &= ~(0x3 << 5);
    handle -> timer -> CR1 |= temp << 5;

    bool temp2 = handle -> timerConfig.autoReloadBufferEnabled;
    handle -> timer -> CR1 &= ~(0x1 << 7);
    handle -> timer -> CR1 |= temp2 << 7;

    temp2 = handle -> timerConfig.timerCountdownModeEnabled;
    handle -> timer -> CR1 &= ~(0x1 << 4);
    handle -> timer -> CR1 |= temp2 << 4;

    temp2 = handle -> timerConfig.interruptUpdateEnabled;
    handle -> timer -> DIER &= ~(0x1 << 0);
    handle -> timer -> DIER |= temp2 << 0;

    temp2 = handle -> timerConfig.disableUpdateEvent;
    handle -> timer -> CR1 &= ~(0x1 << 1);
    handle -> timer -> CR1 |= temp2 << 1;

    temp2 = handle -> timerConfig.onePulseModeEnabled;
    handle -> timer -> CR1 &= ~(0x1 << 3);
    handle -> timer -> CR1 |= temp2 << 3;

    Timer_Init_Channel_1(handle);

    if (handle -> timerConfig.interruptUpdateEnabled && !handle -> timerConfig.disableUpdateEvent)
        Timer_Toggle_Interrupt(handle -> timer, ENABLE);
}

void Timer_Init_Channel_1(Timer_Handle_t* handle) {
    uint32_t temp = handle -> timerConfig.channel1Config.channelMode;
    handle -> timer -> CCMR1 &= ~(0x7 << 4);
    handle -> timer -> CCMR1 |= temp << 4;

    temp = handle -> timerConfig.channel1Config.captureCompareSelection;
    handle -> timer -> CCMR1 &= ~(0x2 << 0);
    handle -> timer -> CCMR1 |= temp << 0;

    temp = handle -> timerConfig.channel1Config.captureCompareValue;
    handle -> timer -> CCR1 &= ~(0xFFFF << 0);
    handle -> timer -> CCR1 |= temp << 0;

    bool temp2 = handle -> timerConfig.channel1Config.outputCompareFastEnabled;
    handle -> timer -> CCMR1 &= ~(0x1 << 2);
    handle -> timer -> CCMR1 |= temp2 << 2;

    temp2 = handle -> timerConfig.channel1Config.outputComparePreloadEnabled;
    handle -> timer -> CCMR1 &= (0x1 << 3);
    handle -> timer -> CCMR1 |= temp2 << 3;

    temp2 = handle -> timerConfig.channel1Config.outputCompareClearEnabled;
    handle -> timer -> CCMR1 &= (0x1 << 7);
    handle -> timer -> CCMR1 |= temp2 << 7;

    temp2 = handle -> timerConfig.channel1Config.outputChannelInterruptEnabled;
    handle -> timer -> DIER &= (0x1 << 1);
    handle -> timer -> DIER |= temp2 << 1;
}

void Timer_Toggle_Clock(GPTIMR_RegDef_t* reg, uint8_t toggle) {
    if (reg == TIM2) {
        if (toggle == ENABLE)
            TIMx_CLOCK_ENABLE(TIM2_OFFSET);
        else
            TIMx_CLOCK_DISABLE(TIM2_OFFSET);
    }
    else if (reg == TIM5) {
        if (toggle == ENABLE)
            TIMx_CLOCK_ENABLE(TIM5_OFFSET);
        else
            TIMx_CLOCK_DISABLE(TIM5_OFFSET);
    }
}

void Timer_Start(GPTIMR_RegDef_t* reg) {
    reg -> CR1 |= (0x1);
}

void Timer_Stop(GPTIMR_RegDef_t* reg) {
    reg -> CR1 &= ~(0x1);
}

void Timer_Reset(GPTIMR_RegDef_t* reg) {
    reg -> CNT &= (0x0);
}

uint32_t Timer_Return_Value(GPTIMR_RegDef_t* reg) {
    return reg -> CNT;
}

void Timer_Toggle_Interrupt(GPTIMR_RegDef_t* reg, uint8_t toggle) {
    if (reg == TIM2) {
        if (toggle == ENABLE)
            InterruptIRQ_Enable(TIM2_IRQ_NUMBER);
        else
            InterruptIRQ_Disable(TIM2_IRQ_NUMBER);
    }
    else if (reg == TIM5) {
        if (toggle == ENABLE)
            InterruptIRQ_Enable(TIM5_IRQ_NUMBER);
        else
            InterruptIRQ_Disable(TIM5_IRQ_NUMBER);
    }
}

void Timer_Change_Priority(GPTIMR_RegDef_t* reg, uint8_t newPriority) {
    if (reg == TIM2) {
        InterruptIRQ_Configure_Priority(TIM2_IRQ_NUMBER, newPriority);
    }
    else if (reg == TIM5) {
        InterruptIRQ_Configure_Priority(TIM5_IRQ_NUMBER, newPriority);
    }
}
