#include "CliThread.h" 
#include "UartDriver/UartDriver.h"
#include <string.h>
#include <kernel.h>
#include <sys/printk.h>

bool isCmdMode = false;
uint8_t cmdStartFrame[] = "hi bhai";
uint8_t cmdStopFrame[] = "bye bhai";

/* uart driver data variable */
extern uartData_t uartTxRx;

/* configuring the cli thread */
K_THREAD_DEFINE(tid_CliThread, CLI_THREAD_STACK_SIZE, CliThread, ARG_1, ARG_2, ARG_3, CLI_THREAD_PRIORITY, 0, 0);

/* print the recieved frame */
void printRecievedFrame() {
  for(uint32_t i=0; i<uartTxRx.rxBufLen; i++) {
      printk("%c", uartTxRx.rxBuf[i]);
  }
  printk("\n");
}

/* check for the mode and take the neccessary actions */
void parseRecievedFrame() {
  /* In cmd mode , we will parse the command but before this kindly check if 
   * user wants to exit the cli or not. 
   */
  if(isCmdMode) {
    printk(":: Cmd Mode ::\n");
    uint32_t rxFrameLen = uartTxRx.rxBufLen;
    uint32_t cmdStopFrameLen = strlen(cmdStopFrame);

    //printk("%d %d\n",strlen(cmdStopFrame), uartTxRx.rxBufLen);
    
    /* let user give info about cmd entered */
    printRecievedFrame();
    
    /* checking for cmd stop cmd */
    if(rxFrameLen == cmdStopFrameLen) {
      if (memcmp(uartTxRx.rxBuf, cmdStopFrame, rxFrameLen) == 0) {
        isCmdMode = false;
        printk("cmd stop frame found, switching to data mode !!\n");
      }
    }
  }
  /* In data mode , we will parse the data but before this kindly check if 
   * user wants to enter the cli or not. 
   */
  else {
    printk(":: Data Mode ::\n");
    uint32_t rxFrameLen = uartTxRx.rxBufLen;
    uint32_t cmdStartFrameLen = strlen(cmdStartFrame);

    //printk("%d %d\n",strlen(cmdStartFrame), uartTxRx.rxBufLen);
    
    /* let user give info about data entered */
    printRecievedFrame();

    /* checking for cmd start cmd */
    if(rxFrameLen == cmdStartFrameLen) {
      if (memcmp(uartTxRx.rxBuf, cmdStartFrame, rxFrameLen) == 0) {
        isCmdMode = true;
        printk("cmd start frame found, switching to cmd mode !!\n");
      }
    }
  }  
}

/* entry point of the thread */
void CliThread(void * arg1, void * arg2, void * arg3) {
  int taskCounter = 0;
  
  for(;;) {
    /* suspend the cli thread */
    k_thread_suspend(tid_CliThread);

    /* give user info about triggering and update the trigger count */
    taskCounter++;
    //printk("%d %d %d : %d !!\n", (int *) arg1, (int *)arg2, (int *)arg3, taskCounter);
    //printk("Cli Thread Triggered : %d !!\n", taskCounter);
    
    /* parse the recieved frame */
    parseRecievedFrame();
  }
}