/*
 * LED_Driver.c
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#include "LED_Driver.h"

static GPIO_Handle_t red;
static GPIO_Handle_t green;

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
