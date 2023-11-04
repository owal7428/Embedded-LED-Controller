/*
 * LED_Driver.c
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#include "LED_Driver.h"

static GPIO_Handle_t red;
static GPIO_Handle_t green;

static Timer_Handle_t TIM2handle;
static Timer_Handle_t TIM5handle;

void LED_Init(uint8_t led) {
    switch (led) {
        case RED_LED:
            red.pGPIOx = GPIOG;
            red.GPIO_PinConfig.PinNumber = RED_LED_PORT;
            red.GPIO_PinConfig.PinMode = PIN_MODE_CONFIG_GPOUT;
            red.GPIO_PinConfig.PinSpeed = OSPEED_MED;
            red.GPIO_PinConfig.OPType = OPTYPE_PUSH_PULL;
            red.GPIO_PinConfig.PinPuPdControl = PUPD_CONTROL_NONE;
            LED_EnableClock(RED_LED);
            GPIO_Init(&red);
            break;

        case GREEN_LED:
            green.pGPIOx = GPIOG;
            green.GPIO_PinConfig.PinNumber = GREEN_LED_PORT;
            green.GPIO_PinConfig.PinMode = PIN_MODE_CONFIG_GPOUT;
            green.GPIO_PinConfig.PinSpeed = OSPEED_MED;
            green.GPIO_PinConfig.OPType = OPTYPE_PUSH_PULL;
            green.GPIO_PinConfig.PinPuPdControl = PUPD_CONTROL_NONE;
            LED_EnableClock(GREEN_LED);
            GPIO_Init(&green);
    }
}
void LED_EnableClock(uint8_t led) {
    switch (led) {
        case RED_LED:
            GPIO_ClockEnableOrDisable(red.pGPIOx, ENABLE);
            break;
        case GREEN_LED:
            GPIO_ClockEnableOrDisable(green.pGPIOx, ENABLE);
    }
}

void LED_Enable(uint8_t led) {
    switch (led) {
        case RED_LED:
            GPIO_Write(GPIOG, red.GPIO_PinConfig.PinNumber, ENABLE);
            break;
        case GREEN_LED:
            GPIO_Write(GPIOG, green.GPIO_PinConfig.PinNumber, ENABLE);
    }
}

void LED_Disable(uint8_t led) {
    switch (led) {
        case RED_LED:
            GPIO_Write(GPIOG, red.GPIO_PinConfig.PinNumber, DISABLE);
            break;
        case GREEN_LED:
            GPIO_Write(GPIOG, green.GPIO_PinConfig.PinNumber, DISABLE);
    }
}

void LED_Toggle(uint8_t led) {
    switch (led) {
        case RED_LED:
            GPIO_Toggle(GPIOG, red.GPIO_PinConfig.PinNumber);
            break;
        case GREEN_LED:
            GPIO_Toggle(GPIOG, green.GPIO_PinConfig.PinNumber);
    }
}

void LED_Timer2_Init() {
    TIM2handle.timer = TIM2;

    TIM2handle.timerConfig.masterModeSelection = MMS_RESET;
    TIM2handle.timerConfig.autoReloadValue = 100;
    TIM2handle.timerConfig.clockDivisionValue = CLOCK_DIVISION_1T;
    TIM2handle.timerConfig.prescalerValue = PRESCALER_DIV8;
    TIM2handle.timerConfig.centerAlignedModeSelect = CENTER_ALIGNED_MODE_EDGE;
    TIM2handle.timerConfig.autoReloadBufferEnabled = true;
    TIM2handle.timerConfig.timerCountdownModeEnabled = false;
    TIM2handle.timerConfig.interruptUpdateEnabled = true;
    TIM2handle.timerConfig.disableUpdateEvent = false;
    TIM2handle.timerConfig.onePulseModeEnabled = false;
    TIM2handle.timerConfig.channel1Config.channelMode = CHANNEL_MODE_FROZEN;
    TIM2handle.timerConfig.channel1Config.captureCompareSelection = CAPTURE_COMPARE_SELECTION_OUTPUT;
    TIM2handle.timerConfig.channel1Config.captureCompareValue = 90;
    TIM2handle.timerConfig.channel1Config.outputCompareFastEnabled = false;
    TIM2handle.timerConfig.channel1Config.outputComparePreloadEnabled = true;
    TIM2handle.timerConfig.channel1Config.outputCompareClearEnabled = false;
    TIM2handle.timerConfig.channel1Config.outputChannelInterruptEnabled = true;

    Timer_Toggle_Clock(TIM2, ENABLE);
    Timer_Init(&TIM2handle);
}
void LED_Timer2_Start() {
    Timer_Start(TIM2);
}
void LED_Timer2_Stop() {
    Timer_Stop(TIM2);
}
void LED_Timer2_Reset() {
    Timer_Reset(TIM2);
}
void LED_Timer2_Priority() {
    Timer_Change_Priority(TIM2, TIM_ELEVATED_PRIORITY);
}
void LED_Timer2_Priority_Reset() {
    Timer_Change_Priority(TIM2, TIM2_DEFAULT_PRIORITY);
}

void LED_Timer5_Init() {
    TIM5handle.timer = TIM5;

    TIM5handle.timerConfig.masterModeSelection = MMS_RESET;
	TIM5handle.timerConfig.autoReloadValue = 100;
	TIM5handle.timerConfig.clockDivisionValue = CLOCK_DIVISION_1T;
	TIM5handle.timerConfig.prescalerValue = PRESCALER_DIV8;
	TIM5handle.timerConfig.centerAlignedModeSelect = CENTER_ALIGNED_MODE_EDGE;
	TIM5handle.timerConfig.autoReloadBufferEnabled = true;
	TIM5handle.timerConfig.timerCountdownModeEnabled = false;
	TIM5handle.timerConfig.interruptUpdateEnabled = true;
	TIM5handle.timerConfig.disableUpdateEvent = false;
	TIM5handle.timerConfig.onePulseModeEnabled = false;
	TIM5handle.timerConfig.channel1Config.channelMode = CHANNEL_MODE_FROZEN;
	TIM5handle.timerConfig.channel1Config.captureCompareSelection = CAPTURE_COMPARE_SELECTION_OUTPUT;
	TIM5handle.timerConfig.channel1Config.captureCompareValue = 100;
	TIM5handle.timerConfig.channel1Config.outputCompareFastEnabled = false;
	TIM5handle.timerConfig.channel1Config.outputComparePreloadEnabled = true;
	TIM5handle.timerConfig.channel1Config.outputCompareClearEnabled = false;
	TIM5handle.timerConfig.channel1Config.outputChannelInterruptEnabled = true;

    Timer_Toggle_Clock(TIM5, ENABLE);
    Timer_Init(&TIM5handle);
}
void LED_Timer5_Start() {
    Timer_Start(TIM5);
}
void LED_Timer5_Stop() {
    Timer_Stop(TIM5);
}
void LED_Timer5_Reset() {
    Timer_Reset(TIM5);
}
void LED_Timer5_Priority() {
    Timer_Change_Priority(TIM5, TIM_ELEVATED_PRIORITY);
}
void LED_Timer5_Priority_Reset() {
    Timer_Change_Priority(TIM5, TIM5_DEFAULT_PRIORITY);
}
