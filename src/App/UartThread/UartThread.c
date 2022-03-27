#include "Cli/Cli.h"  
#include "UartDriver/UartDriver.h"
#include "UartThread/UartThread.h"
#include <string.h>
#include <kernel.h>
#include <sys/printk.h>

/* uart driver data variable */
extern uartData_t uartTxRx;

/* cli extern variables */
extern bool isCliMode;
extern uint8_t cliStartFrame[];
extern uint8_t  cliStopFrame[];

/* configuring the cli thread */
K_THREAD_DEFINE(tid_UartThread, UART_THREAD_STACK_SIZE, UartThread, ARG_1, ARG_2, ARG_3, UART_THREAD_PRIORITY, 0, 0);

/* entry point of the thread */
void UartThread(void * arg1, void * arg2, void * arg3) {
  int taskCounter = 0;
  
  for(;;) {
    /* suspend the cli thread */
    k_thread_suspend(tid_UartThread);

    /* give user info about triggering and update the trigger count */
    taskCounter++;
    //printk("%d %d %d : %d !!\n", (int *) arg1, (int *)arg2, (int *)arg3, taskCounter);
    //printk("Cli Thread Triggered : %d !!\n", taskCounter);

    /* print the recieved frame */
    printRecievedFrame();

    /* parse the recieved frame */
    parseRecievedFrame();
  }
}

void printRecievedFrame() {
  printk("***** new frame recieved *****\n");
  printk("frame : %s\n", uartTxRx.rxBuf);
  printk("framelen : %d\n", uartTxRx.rxBufLen);
  printk("***** new frame recieved *****\n\n");
}

/* check for the mode and take the neccessary actions */
void parseRecievedFrame() {
  /* In cmd mode , we will parse the command but before this kindly check if 
   * user wants to exit the cli or not. 
   */
  if(isCliMode) {
    printk(":: Cmd Mode::\n");
    uint32_t rxFrameLen = uartTxRx.rxBufLen;
    uint32_t cliStopFrameLen = strlen(cliStopFrame);

    //printk("%d %d\n",strlen(cmdStopFrame), uartTxRx.rxBufLen);
    
    /* checking for cmd stop cmd */
    if(rxFrameLen == cliStopFrameLen) {
      if(memcmp(uartTxRx.rxBuf, cliStopFrame, rxFrameLen) == 0) {
        Cli_Destroy();
      }
      else {
        parseCommandFrame(uartTxRx.rxBuf, uartTxRx.rxBufLen);
      }
    }
    else {
      parseCommandFrame(uartTxRx.rxBuf, uartTxRx.rxBufLen);
    }
  }
  /* In data mode , we will parse the data but before this kindly check if 
   * user wants to enter the cli or not. [default mode] 
   */
  else {
    printk(":: Data Mode ::\n");
    uint32_t rxFrameLen = uartTxRx.rxBufLen;
    uint32_t cliStartFrameLen = strlen(cliStartFrame);

    //printk("%d %d\n",strlen(cmdStartFrame), uartTxRx.rxBufLen);

    /* checking for cmd start cmd */
    if(rxFrameLen == cliStartFrameLen) {
      if(memcmp(uartTxRx.rxBuf, cliStartFrame, rxFrameLen) == 0) {
        Cli_Create();
      }
      else {
        parseDataFrame(uartTxRx.rxBuf, uartTxRx.rxBufLen);
      }
    }
    else {
      parseDataFrame(uartTxRx.rxBuf, uartTxRx.rxBufLen);
    }
  }  
}

/* I will parse the incoming data */
void parseDataFrame(const char * dataFrame, const uint32_t dataFrameLen) {
  printk("Hi, I will parse this data !!\n\n");

  /* do something here */


}

/* Iwill parse the incoming command */
void parseCommandFrame(const char * cmdFrame, const uint32_t cmdFrameLen) {
  printk("Hi, I will parse this cmd !!\n\n");

  /* do something here */
    
  //char cmd[20] = "";
  //char args[20] = "";
  
  //int wtIndex = 0;
  //char * ptr = cmd;
  //for(int i=0; i<cmdFrameLen; i++) {
  //  if(cmdFrame[i] == ':') {
  //    wtIndex = 0;
  //    ptr = args;
  //    continue;
  //  }
  //  ptr[wtIndex++] = cmdFrame[i];
  //}

  //printk("cmd : %s\n", cmd);
  //printk("args : %s\n", args);

  //int retVal;
  //bool isCmdFound = false;
  
  ///* loop over all the led commands, If matches to any available command then call the
  // * respective api using function pointer and set the flag and break the looping 
  // */
  //for(int i=0; i<ledCmdListLen; i++) {
  //  if(strcmp(cmd, ledCmdList[i].cmd) == 0) {
  //    retVal = (ledCmdList[i].handler)(1,args);
  //    printk("retVal : %d\n", retVal);
  //    isCmdFound = true;
  //    break;
  //  }
  //}

  ///* If command is not found then let user know about it */
  //if(!isCmdFound) {
  //  printk("Unknown Command\n");
  //}
}