#include "Button_Driver.h"

GPIO_Handle_t button = {0};

void Button_Init() {
    button.pGPIOx = BUTTON_PORT;
    button.GPIO_PinConfig.PinNumber = BUTTON_PIN_NUM;
    button.GPIO_PinConfig.PinMode = PIN_MODE_CONFIG_GPIN;
    button.GPIO_PinConfig.PinSpeed = OSPEED_MED;
    button.GPIO_PinConfig.OPType = OPTYPE_PUSH_PULL;
    button.GPIO_PinConfig.PinPuPdControl = PUPD_CONTROL_NONE;
    Button_EnableClock();
    GPIO_Init(&button);
}

void Button_InitInterruptMode() {
    button.pGPIOx = BUTTON_PORT;
    button.GPIO_PinConfig.PinNumber = BUTTON_PIN_NUM;
    button.GPIO_PinConfig.PinMode = PIN_MODE_CONFIG_GPIN;
    button.GPIO_PinConfig.PinSpeed = OSPEED_MED;
    button.GPIO_PinConfig.OPType = OPTYPE_PUSH_PULL;
    button.GPIO_PinConfig.PinPuPdControl = PUPD_CONTROL_NONE;
    button.GPIO_PinConfig.PinInterruptMode = FALLING_AND_RISING_INTERRUPT;
    Button_EnableClock();
    GPIO_Init(&button);
    GPIO_EnableOrDisableInterrupt(EXTI0_IRQ_NUMBER, ENABLE);
}

void Button_EnableClock() {
    GPIO_ClockEnableOrDisable(button.pGPIOx, ENABLE);
}

bool Button_IsPressed() {
    uint8_t val = GPIO_ReadFromPin(button.pGPIOx, button.GPIO_PinConfig.PinNumber);

    if (val == BUTTON_PRESSED)
        return true;
    else if (val == BUTTON_NOT_PRESSED)
        return false;
    return false;
}
