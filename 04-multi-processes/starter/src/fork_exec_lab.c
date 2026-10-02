#include "fork_exec_lab.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int g_counter = 100;

pid_t spawn_child(void) {
    return fork();
}

int run_child_process(int *heap_counter, int stack_counter) {
    int child_sum;

    /* TODO: Update all three counters in the child by +7. */
    /* TODO: Compute child_sum as the sum of the updated counters. */
    /* TODO: Print exactly: child: g=<g> h=<h> s=<s> sum=<sum> */
    /* TODO: Return child_sum % 256. */

    (void)heap_counter;
    (void)stack_counter;
    (void)child_sum;
    fprintf(stderr, "TODO: child address-space logic not implemented\n");
    return 1;
}

int wait_for_child(pid_t child_pid, int *heap_counter, int stack_counter) {
    int status = 0;
    int child_code;

    if (waitpid(child_pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    if (!WIFEXITED(status)) {
        fprintf(stderr, "parent: child terminated abnormally\n");
        return 1;
    }

    child_code = WEXITSTATUS(status);

    /* TODO: Print exactly: parent: child-exit=<code> */
    /* TODO: Print exactly: parent: g=<g> h=<h> s=<s> */
    /* TODO: If parent values are 100, 200, 300 print:
       parent: address-space=isolated
       Otherwise print:
       parent: address-space=unexpected */
    /* TODO: Return 0 only if child_code is 109 and parent values are unchanged. */

    (void)status;
    (void)child_code;
    (void)heap_counter;
    (void)stack_counter;
    fprintf(stderr, "TODO: parent reporting not implemented\n");
    return 1;
}

int main(void) {
    pid_t child_pid;
    int *heap_counter;
    int stack_counter = 300;

    heap_counter = malloc(sizeof(*heap_counter));
    if (heap_counter == NULL) {
        perror("malloc");
        return 1;
    }
    *heap_counter = 200;

    printf("parent: start g=%d h=%d s=%d\n", g_counter, *heap_counter, stack_counter);
    fflush(stdout);

    child_pid = spawn_child();
    if (child_pid < 0) {
        perror("fork");
        free(heap_counter);
        return 1;
    }

    if (child_pid == 0) {
        int child_rc = run_child_process(heap_counter, stack_counter);
        free(heap_counter);
        return child_rc;
    }

    {
        int parent_rc = wait_for_child(child_pid, heap_counter, stack_counter);
        free(heap_counter);
        return parent_rc;
    }
}