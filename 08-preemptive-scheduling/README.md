# 08 - Preemptive Scheduling

Basic preemptive round-robin scheduler: the SysTick ISR doubles as the
context-switch trigger (`svc_handler`/`systick_handler` share the same
save/restore code in `context_switch.S`), so tasks are interrupted on a
timer instead of having to yield voluntarily.

## Build & run

```
make
make qemu
```
