#ifndef SYSTICK_H
#define SYSTICK_H

/* STM32F429 is 180MHz */
#define CPU_CLOCK_HZ 180000000

/* 100 ms per tick. */
#define TICK_RATE_HZ 10

void SysTick_init(void);

#endif
