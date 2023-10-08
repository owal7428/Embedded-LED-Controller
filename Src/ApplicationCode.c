/*
 * ApplicationCode.c
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#include "ApplicationCode.h"

uint8_t currentLED;

// I'm using the green LED here
void ApplicationInit() {
    InitGreenLED();
    InitRedLED();

    currentLED = GREEN_LED;

    DisableGreenLED();
    DisableRedLED();

    addSchedulerEvent(DELAY_EVENT);

    #if BUTTON_INTERRUPT_ENABLE == 0
    InitButton();
    addSchedulerEvent(BUTTON_POLL);
    #else
    InitButtonInterruptMode();
    #endif
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
    InterruptIRQ_disable(EXTI0_IRQ_NUMBER);

    if (currentLED == GREEN_LED)
        ToggleGreenLED();
    else if (currentLED == RED_LED)
        ToggleRedLED();
    
    EXTI_clear_pending(BUTTON_PIN_NUM);

    InterruptIRQ_enable(EXTI0_IRQ_NUMBER);
}
