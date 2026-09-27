# 04 - Basic Context Switch

Introduces the basic switch from kernel (handler) mode to user
(thread) mode: `activate()` in `context_switch.S` sets `PSP`, flips the
`CONTROL` register to unprivileged/process-stack, and branches into a
single user task that never returns to the kernel.

## Build & run

```
make
make qemu
```
