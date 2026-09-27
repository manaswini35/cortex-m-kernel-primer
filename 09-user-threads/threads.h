#ifndef THREADS_H
#define THREADS_H

void thread_start(void);
int thread_create(void (*run)(void *), void *userdata);
void thread_kill(int thread_id);
void thread_self_terminal(void);

#endif
