#include "GPIO_Driver.h"

#define BUTTON_PORT GPIOA
#define BUTTON_PIN_NUM GPIO_PIN_0

#define BUTTON_PRESSED 1
#define BUTTON_NOT_PRESSED 0

void Button_Init();
void Button_InitInterruptMode();

void Button_EnableClock();

bool Button_IsPressed();
