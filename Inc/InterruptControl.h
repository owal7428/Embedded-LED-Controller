#include "STM32F429i.h"

#define EXTI0_IRQ_NUMBER 6

void InterruptIRQ_enable(uint8_t IRQ);
void InterruptIRQ_disable(uint8_t IRQ);
void InterruptIRQ_clear_pending(uint8_t IRQ);
void InterruptIRQ_set_pending(uint8_t IRQ);

void EXTI_clear_pending(uint8_t pin_num);