# 05 - Context Switch via Syscall

Builds on `04-context-switch-basic` by introducing `svc` as the way a user
task returns to kernel mode. `syscall.S` triggers `svc 0`, and
`svc_handler` in `context_switch.S` saves the user state and hands
control back to `activate()`'s caller, which can resume the task later.

## Build & run

```
make
make qemu
```
