#include "CliThread.h" 
#include <kernel.h>
#include <sys/printk.h>

/* configuring the cli thread */
K_THREAD_DEFINE(tid_CliThread, CLI_THREAD_STACK_SIZE, CliThread, ARG_1, ARG_2, ARG_3, CLI_THREAD_PRIORITY, 0, 0);

/* entry point of the thread */
void CliThread(void * arg1, void * arg2, void * arg3) {
  int taskCounter = 0;
  
  for(;;) {
    
    /* suspend the cli thread */
    k_thread_suspend(tid_CliThread);

    /* give user info about triggering and update the trigger count */
    taskCounter++;
    printk("%d %d %d : %d !!\n", (int *) arg1, (int *)arg2, (int *)arg3, taskCounter);
    printk("Cli Thread Triggered : %d !!\n", taskCounter);

  }
}