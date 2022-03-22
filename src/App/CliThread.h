#ifndef A_CliThread_H
#define A_CliThread_H


/* arguments to entry point of the cli thread */
#define ARG_1 10
#define ARG_2 20
#define ARG_3 30

/* cli thread priority */
#define CLI_THREAD_PRIORITY 1

/* cli thread stack size */
#define CLI_THREAD_STACK_SIZE 1024

/* declares the entry point of the thread */
void CliThread(void * arg1, void * arg2, void * arg3);


#endif /* A_CliThread_H */