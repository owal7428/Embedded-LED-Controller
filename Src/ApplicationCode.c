/*
 * ApplicationCode.c
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#include "ApplicationCode.h"

uint8_t currentLED;

static int redStatus;
static int greenStatus;

// I'm using the green LED here
void ApplicationInit() {
    InitGreenLED();
    InitRedLED();

    DisableGreenLED();
    DisableRedLED();

    redStatus = LED_OFF;
    greenStatus = LED_OFF;

    #if BUTTON_INTERRUPT_ENABLE == 0
    InitButton();
    addSchedulerEvent(BUTTON_POLL);
    #else
    InitButtonInterruptMode();
    #endif
    
    LED_Timer2_Init();
    LED_Timer5_Init();

    LED_Timer2_Start();
    LED_Timer5_Start();

    addSchedulerEvent(DELAY_EVENT);

}

void InitGreenLED() {
    LED_Init(GREEN_LED);
}

void InitRedLED() {
    LED_Init(RED_LED);
}

void InitRedGreenLEDs() {
    InitGreenLED();
    InitRedLED();
}

void ToggleGreenLED() {
    LED_Toggle(GREEN_LED);
}

void ToggleRedLED() {
    LED_Toggle(RED_LED);
}

void EnableGreenLED() {
    LED_Enable(GREEN_LED);
}
void EnableRedLED() {
    LED_Enable(RED_LED);
}

void DisableGreenLED() {
    LED_Disable(GREEN_LED);
}

void DisableRedLED() {
    LED_Disable(RED_LED);
}

#if BUTTON_INTERRUPT_ENABLE == 0
void InitButton() {
    Button_Init();
}

void ButtonPollingRoutine() {
    switch (Button_IsPressed()) {
        case BUTTON_PRESSED:
            if (currentLED == GREEN_LED)
                EnableGreenLED();
            else if (currentLED == RED_LED)
                EnableRedLED();
            break;
        case BUTTON_NOT_PRESSED:
            if (currentLED == GREEN_LED)
                DisableGreenLED();
            else if (currentLED == RED_LED)
                DisableRedLED();  
            break;
    }
}
#else
void InitButtonInterruptMode() {
    Button_InitInterruptMode();
}
#endif

void Delay(uint32_t delay) {
    char name[] = "OwenAllison";
    [[maybe_unused]] char temp[NAME_LENGTH];

    for (int i = 0; i < MAGNIFY; i++) {
        for (int i = 0; i < NAME_LENGTH; i++) {
            temp[i] = name[i];
        }
    }
}

void EXTI0_IRQHandler(void) {
    InterruptIRQ_Disable(EXTI0_IRQ_NUMBER);

    // Re-enable TIM2's interrupt
    *NVIC_SET_ENABLE |= (0x1 << TIM2_IRQ_NUMBER);

    #if USE_LIMITED_RESOURCES == 1
    DisableGreenLED();
    DisableRedLED();
    redStatus = LED_OFF;
    greenStatus = LED_OFF;
    #else
    // Reset LEDs
    LED_Timer2_Reset();
    LED_Timer5_Reset();
    #endif

    EXTI_Clear_Pending(BUTTON_PIN_NUM);

    InterruptIRQ_Enable(EXTI0_IRQ_NUMBER);
}

void TIM2_IRQHandler(void) {
    InterruptIRQ_Disable(TIM2_IRQ_NUMBER);

    // Re-enable EXTI0's interrupt
    *NVIC_SET_ENABLE |= (0x1 << EXTI0_IRQ_NUMBER);

    uint32_t flags = TIM2 -> SR;
    bool countedFlag = flags & (0x1 << 1);

    // If bit 1 of SR register is set
    if (countedFlag)
    {

        #if USE_LIMITED_RESOURCES == 1
        if (greenStatus == LED_OFF) {
            LED_Timer2_Priority();
			ToggleRedLED();
			redStatus += 1; redStatus %= 2;
        }
        else {
        	DisableRedLED();
        	redStatus = LED_OFF;
            LED_Timer2_Priority_Reset();
        }
        #else
        ToggleRedLED();
        redStatus += 1; redStatus %= 2;
        #endif
    }

    TIM2 -> SR &= ~(0x1 << 1);

    InterruptIRQ_Clear_Pending(TIM2_IRQ_NUMBER);

    InterruptIRQ_Enable(TIM2_IRQ_NUMBER);
}

void TIM5_IRQHandler(void) {
    InterruptIRQ_Disable(TIM5_IRQ_NUMBER);

    uint32_t flags = TIM5 -> SR;
    bool countedFlag = flags & (0x1 << 1);

    // If bit 1 of SR register is set
    if (countedFlag)
    {

        #if USE_LIMITED_RESOURCES == 1
        if (redStatus == LED_OFF) {
            LED_Timer5_Priority();
			ToggleGreenLED();
			greenStatus += 1; greenStatus %= 2;
        }
        else {
        	DisableGreenLED();
        	greenStatus = LED_OFF;
            LED_Timer5_Priority_Reset();
        }
        #else
        ToggleGreenLED();
        greenStatus += 1; greenStatus %= 2;
        #endif
    }

    TIM5 -> SR &= ~(0x1 << 1);

    InterruptIRQ_Clear_Pending(TIM5_IRQ_NUMBER);

    InterruptIRQ_Enable(TIM5_IRQ_NUMBER);
}
