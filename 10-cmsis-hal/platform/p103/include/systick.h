#ifndef SYSTICK_H
#define SYSTICK_H

/* STM32P103 is 72MHz */
#define CPU_CLOCK_HZ 72000000

/* 100 ms per tick. */
#define TICK_RATE_HZ 10

void SysTick_init(void);

#endif
