#include "InterruptControl.h"

void InterruptIRQ_enable(uint8_t IRQ)
{
    uint8_t shift = IRQ % 32;
    *NVIC_SET_ENABLE |= (1 << shift);
}

void InterruptIRQ_disable(uint8_t IRQ)
{
    uint8_t shift = IRQ % 32;
    *NVIC_CLEAR_ENABLE |= (1 << shift);
}

void InterruptIRQ_clear_pending(uint8_t IRQ)
{
	uint8_t shift = IRQ % 32;
	*NVIC_CLEAR_PENDING |= (1 << shift);
}

void InterruptIRQ_set_pending(uint8_t IRQ)
{
    uint8_t shift = IRQ % 32;
	*NVIC_SET_PENDING |= (1 << shift);
}

void EXTI_clear_pending(uint8_t pin_num)
{
    EXTI -> PR |= (1 << pin_num);
}
