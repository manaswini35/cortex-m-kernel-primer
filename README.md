cortex-m-kernel-primer
=======================

Build a minimal multi-tasking OS kernel for ARM from scratch.

Prerequisites
-------------
- [QEMU with an STM32 microcontroller implementation](https://github.com/beckus/qemu_stm32)
  - Build instructions
```
./configure --disable-werror --enable-debug \
    --target-list="arm-softmmu" \
    --extra-cflags=-DSTM32_UART_NO_BAUD_DELAY \
    --extra-cflags=-DSTM32_UART_ENABLE_OVERRUN \
    --disable-gtk
make
```
- [GNU Toolchain for ARM](https://launchpad.net/gcc-arm-embedded)
- Set `$PATH` accordingly

Stages
------
* `01-semihosting-hello-world`
  - Minimal semihosted ARM Cortex-M "Hello World"
* `02-uart-hello-world`
  - Enable STM32 USART to print trivial greetings
* `03-improved-startup`
  - Almost identical to the previous one but improved startup routines
* `04-context-switch-basic`
  - Basic switch between user and kernel mode
* `05-context-switch-syscall`
  - System call is introduced as an effective method to return to kernel
* `06-multitasking`
  - Two user tasks are cooperatively switching
* `07-timer-interrupt`
  - Enable SysTick for future scheduler implementation
* `08-preemptive-scheduling`
  - Basic preemptive scheduling
* `09-user-threads`
  - Implement user-level threads
* `10-cmsis-hal`
  - Illustrate hardware abstraction layer (HAL) by introducing CMSIS
  - Both emulator (based on stm32-p103) and real device (STM32F429i
    discovery) are supported.

Building and Verification
--------------------------
Change the current working directory to the specified stage and then:
```
make
make qemu
```

Guide to Hacking 10-cmsis-hal
==============================
`10-cmsis-hal` implements preemptive round-robin scheduling with
user-level threads for STM32F429i-Discovery (real device) and
STM32-P103 (qemu).

## Get the dependencies:
```
git submodule init
git submodule update
```

Install additional utilities:
- If you would like to verify the kernel on STM32F29i-Discovery, you should
  install:
  * [st-link](https://github.com/texane/stlink) or [OpenOCD](http://openocd.org/)
  - [NeoCon](http://wiki.openmoko.org/wiki/NeoCon) or [screen](http://www.commandlinefu.com/commands/view/6130/use-screen-as-a-terminal-emulator-to-connect-to-serial-consoles)


## Quick Start / Support Devices:
- [STM32F429i-Discovery(physical devices)](http://www2.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-mcu-discovery-kits/32f429idiscovery.html)
  - STM32F429i-Discovery uses `USART1(Tx=PA9,Rx=PA10,baud rate=115200)` as default serial port here.
    - You would need a terminal emulator, such as `screen`
      - Installation on Ubuntu / Debian based systems:
      `sudo apt-get install screen`
      - Then, attach the device file where a serial to USB converter is attached:
      `screen /dev/ttyUSB0 115200 8n1`
      - Once you want to quit screen, press: `Ctrl-a` then `k`

## Available commands:
**Overall**
  - `make all`
    - Build all target's bin,elf,objdump files in the "release" directory.
    - NOTE: `make` does NOT equal `make all` here because the Makefile
      uses `eval` for `targets`.
  - `make clean`
    - Remove the entire "release" directory.

**STM32-P103(QEMU)**
  - `make p103` or `make target PLAT=p103`
    - Build "p103.bin"
  - `make qemu`
    - Build "p103.bin" and run QEMU automatically.
  - `make qemu_GDBstub`
    - Build "p103.bin" and run QEMU with GDB stub and wait for remote
      GDB automatically.
  - `make qemu_GDBconnect`
    - Open remote GDB to connect to the QEMU GDB stub with port:1234 (the
      default port).

**STM32F429i-Discovery(physical device)**
  - `make f429disco` or `make target PLAT=f429disco`
    - Build "f429disco.bin"
  - `make st-flash`
    - Build "f429disco.bin" and flash the binary into STM32F429 with st-link.
  - `make st-erase`
    - Sometimes, STM32F429i-Discovery will not be able to flash new binary
      file, then you will need to erase flash memory with st-link.
    - Erase the entire flash on STM32F429.
  - `make gdb_ST-UTIL`
    - Using GDB with ST-LINK on STM32F429.
    - Remember to open another terminal, and type "st-util" to open
      "STLINK GDB Server"

## Directory Tree:
- core
  - Hardware independent source and header files.
- platform
  - Hardware dependent source and header files.
- cmsis
  - With cmsis, porting would be much easier!
- release
  - This directory will be created after "Target" in Makefile is called.
  - Containing the elf,bin,objdump files in corresponding directory.
  - `make clean` will remove the entire directory, do not put personal
    files inside it!

## Porting Guide:
You should know what [CMSIS](http://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php) is and why it saves us a lot of efforts.

The full project can be divided into two layers:
- hardware-dependent part (HAL)
  - "platform" directory
- hardware-independent part
  - "core" directory

## Steps to launch the kernel on real devices:
### STEP 1
Select a target name for your device, such as `f429disco`.

In this guide, we assume its name is `example_device` with vendor name "f429disco".

Create `example_device` directory in "platform" and `f429disco`
directory in "cmsis" directory.

Create "include" and "src" directory in `platform/example_device/`

### STEP 2
Introducing your CMSIS for your target, where it should be in the [mbed repo](https://github.com/ARMmbed/mbed-os/tree/master/cmsis).

For example, the CMSIS for STM32F429i-discovery could be found [here](https://github.com/ARMmbed/mbed-os/tree/master/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F429xI).

We only need ".h" files, do not copy any ".c" files.

Put the header files into `cmsis/f429disco/example_device`.

`NOTE:`
You may encounter some error messages during building binary for your target.
You need to solve it manually.
Usually, some files may be missing caused by some specific "define".
You could just comment out that definition to resolve this problem.

### STEP 3
This is the most difficult part.

You have to implement the files in `platform/example_device/include/` and
`platform/example_device/src/`.

According to different device vendor (such as STMicroelectronics, NXP, etc), the
implementation is very different.

Please look into the current example: `f429disco`, and you will figure it out!

The function interface must be the same as the function interface in
`platform/p103/include/` due to this being the HAL for the entire project.

### STEP 4
Add your target rules into the Makefile.

Please look at the example `f429disco` in the Makefile.

Most of the rules are reusable, so all you need is copy-and-paste, modifying
the variable/target name and knowing what gcc arguments suit your target!

- `rules.mk`
  - You should `NOT` modify this file!
  - All of the rules are encapsulated into macros, used in `Makefile`.
- `Makefile`:
  - If your device vendor name does not exist, create a new variable and
    assign a name to it!
    - E.g. `STM32 := STM32`
  - Add your device name
    - E.g. `STM32F429_DEVICE := f429disco`
  - Check your device CPU type (Cortex-M3/4)
    - In `target_using_CM4_list`
  - Will you use CMSIS?
    - If NOT, add to `target_NOT_using_CMSIS_list`
  - Use the predefined macro to produce the corresponding directory and
    device specific variable (device name, vendor name)
    - E.g. `$(eval $(call eval_all_variable,$(STM32F429_DEVICE),$(STM32)))`
    - The `vendor name` is used in the `cmsis` directory name. They must be
      associated with each other.
  - Use the predefined macro to produce the corresponding GCC commands
    - E.g.: `$(eval $(call eval_build_command,$(STM32F429_DEVICE)))`
    - This will derive lots of variables that you don't see in the `Makefile`.
  - Add your device name to `all`
    - In the specific form: `$($(YOUR_DEVICE_NAME)_TARGET)`, this variable
      will be automatically derived by `rules.mk`
    - E.g.: `$($(STM32F429_DEVICE)_TARGET)`

### STEP 5
Congratulations!

Now, you can try the "Available commands" above.

Reference
---------
* [mini-arm-os](https://github.com/jserv/mini-arm-os) - the original project this repository is based on
* [Baking Pi – Operating Systems Development](http://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/)
