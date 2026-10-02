#ifndef FORK_EXEC_LAB_H
#define FORK_EXEC_LAB_H

#include <sys/types.h>

extern int g_counter;

pid_t spawn_child(void);
int run_child_process(int *heap_counter, int stack_counter);
int wait_for_child(pid_t child_pid, int *heap_counter, int stack_counter);

#endif