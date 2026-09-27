# 07 - Timer Interrupt

Enables the Cortex-M SysTick timer and installs `systick_handler` in the
vector table, laying the groundwork for a preemptive scheduler in the
next stage. Each tick currently just prints a message from the ISR.

## Build & run

```
make
make qemu
```
