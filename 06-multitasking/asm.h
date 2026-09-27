#ifndef ASM_H
#define ASM_H

unsigned int *activate(unsigned int *stack);
void task_init_env(unsigned int *stack);
void syscall(void);

#endif
