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

/* configuring the uart thread */
K_THREAD_DEFINE(tid_UartThread, UART_THREAD_STACK_SIZE, UartThread, ARG_1, ARG_2, ARG_3, UART_THREAD_PRIORITY, 0, 0);

/*
 * @brief Function represents the entry point of the uart thread. 
 *
 * @param arg1 pointer to dummy arg1.
 * @param arg1 pointer to dummy arg2.
 * @param arg1 pointer to dummy arg3.
 *
 * @retval None.
 *
 */
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

/*
 * @brief Function to print the recived frame. 
 *
 * @param None.
 *
 * @retval None.
 *
 */
void printRecievedFrame() {
  printk("***** new frame recieved *****\n");
  printk("frame : %s\n", uartTxRx.rxBuf);
  printk("framelen : %d\n", uartTxRx.rxBufLen);
  printk("***** new frame recieved *****\n\n");
}

/*
 * @brief Function to check for the mode and based on it either switch the mode or take 
 * the neccessary actions. 
 *
 * @param None.
 *
 * @retval None.
 *
 */
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
        printk("cli stop frame found, switching back to data mode !!\n");
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
        printk("cli start frame found, switching to cli mode !!\n");
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

/*
 * @brief Function to parse the recieved data. 
 *
 * @param dataFrame    pointer to the data buffer.
 * @param dataFrameLen length of the data buffer.
 *
 * @retval None.
 *
 */
void parseDataFrame(const char * dataFrame, const uint32_t dataFrameLen) {
  printk("Hi, I will parse this data !!\n\n");

  /* do something here */
}

/*
 * @brief Function to parse the recieved cmd. 
 *
 * @param cmdFrame    pointer to the cmd buffer.
 * @param cmdFrameLen length of the cmd buffer.
 *
 * @retval None.
 *
 */
void parseCommandFrame(const char * cmdFrame, const uint32_t cmdFrameLen) {
  printk("Hi, I will parse this cmd !!\n\n");

  /* do something here */
  Cli_Process(cmdFrame, cmdFrameLen);
}