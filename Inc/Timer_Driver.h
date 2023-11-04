/*
 * Timer_Driver.h
 *
 *  Created on: Oct 10, 2023
 *      Author: owenallison
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include "STM32F429i.h"
#include "InterruptControl.h"

#define CHANNEL_MODE_FROZEN 0
#define CHANNEL_MODE_ACTIVE 1
#define CHANNEL_MODE_INACTIVE 2
#define CHANNEL_MODE_TOGGLE 3
#define CHANNEL_MODE_FORCE_INACTIVE 4
#define CHANNEL_MODE_FORCE_ACTIVE 5
#define CHANNEL_MODE_PWM1 6
#define CHANNEL_MODE_PWM2 7

#define CAPTURE_COMPARE_SELECTION_OUTPUT 0
#define CAPTURE_COMPARE_SELECTION_INPUT_TI1 1
#define CAPTURE_COMPARE_SELECTION_INPUT_TI2 2
#define CAPTURE_COMPARE_SELECTION_INPUT_TRC 3

#define MMS_RESET 0
#define MMS_ENABLE 1
#define MMS_UPDATE 2
#define MMS_COMPARE_PULSE 3
#define MMS_COMPARE_OC1REF 4
#define MMS_COMPARE_OC2REF 5
#define MMS_COMPARE_OC3REF 6
#define MMS_COMPARE_OC4REF 7

#define CLOCK_DIVISION_1T 0
#define CLOCK_DIVISION_2T 1
#define CLOCK_DIVISION_4T 2

#define PRESCALER_OFF 0
#define PRESCALER_DIV2 1
#define PRESCALER_DIV4 2
#define PRESCALER_DIV8 3

#define CENTER_ALIGNED_MODE_EDGE 0
#define CENTER_ALIGNED_MODE_1 1
#define CENTER_ALIGNED_MODE_2 2
#define CENTER_ALIGNED_MODE_3 3

typedef struct
{
    uint8_t channelMode;                // Used in CCMR1
    uint8_t captureCompareSelection;
    uint16_t captureCompareValue;       // Used in CCR1
    bool outputCompareFastEnabled;
    bool outputComparePreloadEnabled;
    bool outputCompareClearEnabled;
    bool outputChannelInterruptEnabled; // Used in DIER

} GPTimer_Channel_Config_t;

typedef struct
{
    uint16_t autoReloadValue;           // Used in ARR
    uint8_t masterModeSelection;        // Used in CR2
    uint8_t clockDivisionValue;         // Used in CR1
    uint8_t prescalerValue;             // Used in SMCR
    uint8_t centerAlignedModeSelect;    // Used in CR1
    bool autoReloadBufferEnabled;        // Used in CR1
    bool timerCountdownModeEnabled;       // Used in CR1
    bool interruptUpdateEnabled;        // Used in DIER (bit 0)
    bool disableUpdateEvent;            // Used in CR1 (bit 1)
    bool onePulseModeEnabled;            // Used in CR1 (bit 3)
    GPTimer_Channel_Config_t channel1Config;

} GPTimer_Config_t;

typedef struct
{
    GPTIMR_RegDef_t* timer;
    GPTimer_Config_t timerConfig;

} Timer_Handle_t;

void Timer_Init(Timer_Handle_t* handle);
void Timer_Init_Channel_1(Timer_Handle_t* handle);
void Timer_Toggle_Clock(GPTIMR_RegDef_t* reg, uint8_t toggle);

void Timer_Start(GPTIMR_RegDef_t* reg);
void Timer_Stop(GPTIMR_RegDef_t* reg);
void Timer_Reset(GPTIMR_RegDef_t* reg);

uint32_t Timer_Return_Value(GPTIMR_RegDef_t* reg);

void Timer_Toggle_Interrupt(GPTIMR_RegDef_t* reg, uint8_t toggle);
void Timer_Change_Priority(GPTIMR_RegDef_t* reg, uint8_t newPriority);


#endif /* TIMER_DRIVER_H_ */
