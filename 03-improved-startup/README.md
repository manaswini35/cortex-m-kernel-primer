# 03 - Improved Startup

Almost identical to `02-uart-hello-world`, but with a proper `startup.c`:
it copies initialized `.data` from flash to RAM, zero-fills `.bss`, brings
up the HSE clock via `rcc_clock_init()`, and installs NMI/hard-fault
handlers in the vector table before jumping to `main()`.

## Build & run

```
make
make qemu
```
