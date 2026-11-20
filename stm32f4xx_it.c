#include "stm32f4xx.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}
