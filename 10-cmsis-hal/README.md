# 10 - CMSIS Hardware Abstraction Layer

Illustrates a hardware abstraction layer by introducing CMSIS. The
hardware-independent scheduler/thread/malloc code lives in `core/`, and
per-device register access, startup, UART and SysTick code lives in
`platform/<device>/`. Both the QEMU-emulated STM32-P103 (`p103`) and the
real STM32F429i-Discovery board (`f429disco`) are supported.

## Directory layout

- `core/` - hardware-independent scheduler, thread, malloc, and stream code.
- `platform/<device>/` - hardware-dependent startup, register maps, UART
  and SysTick drivers for that device.
- `cmsis/` - CMSIS device header submodule (see `cmsis/README.md`).
- `rules.mk` - shared Makefile macros; not meant to be edited per-target.

## Build & run

```
make p103            # or: make target PLAT=p103
make qemu             # build p103 and run it under QEMU
make f429disco        # or: make target PLAT=f429disco
make st-flash         # build f429disco and flash via st-link
```

See the top-level README's CMSIS porting guide for adding a new device.
