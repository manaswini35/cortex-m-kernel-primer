#ifndef ASM_H
#define ASM_H

unsigned int *activate(unsigned int *stack);
void *init_activate_env(unsigned int *stack);
void syscall(void);

#endif
