# 01 - Semihosting Hello World

Minimal semihosted ARM Cortex-M "Hello World". Uses the `bkpt 0xab`
semihosting call to print through the debugger/emulator instead of a real
UART peripheral, so it needs no hardware setup at all.

## Build & run

```
make
make qemu
```
