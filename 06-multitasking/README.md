# 06 - Multitasking

Two user tasks (`task1_func`, `task2_func`) are created with their own
stacks and cooperatively switched by the kernel's main loop, alternating
control every time a task calls `syscall()` to yield back.

## Build & run

```
make
make qemu
```
