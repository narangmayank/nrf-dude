#include "Cli/Cli.h"
#include "TestRunner.h"  
#include "Cli/CmdHandler.h"
#include "LedDriver/LedDriver.h"
#include "UartDriver/UartDriver.h"
#include <string.h>
#include <stdlib.h>
#include <sys/printk.h>
#include <unity_fixture.h>

uint8_t Cmd_uartDevRxBuf[20] = "";
const struct device * Cmd_uartDev = NULL;

/*********************************** unit tests command handler's starts ***********************************/


/* run unit tests command handler */
int Cmd_UnitTestsHandler(char * argv) {
  int argc = 2;
  const char * args[] = {"dummy_arg" , "-v"};
  return UnityMain(argc, args, RunAllTestGroups);
}

/* run led unit tests command handler */
int Cmd_LedUnitTestsHandler(char *argv) {
  int argc = 2;
  const char * args[] = {"dummy_arg" , "-v"};
  return UnityMain(argc, args, RunLedTestGroup);
}


/***********************************  unit tests command handler's ends  ***********************************/


/*********************************** led module command handler's starts ***********************************/


/* led instance create command handler */
int Cmd_LedCreateHandler(char * argv) {
  return LedDriver_Create();
}

/* led instance destroy command handler */
int Cmd_LedDestroyHandler(char * argv) {
  return LedDriver_Destroy();
}

/* led On command handler */
int Cmd_LedOnHandler(char * argv) {
  if(strcmp(argv, "") == 0) {
    printk("bhai kya kar rha hai tu, konsi led on karu ye to bta?\n");
    return 22;
  }

  if(strcmp(argv, " all") == 0) {
    return  LedDriver_TurnAllOn();
  }

  uint32_t index = atoi(argv);
  printk("led index : %d\n", index);
  return LedDriver_TurnOn(index);
}

/* led Off command handler */
int Cmd_LedOffHandler(char * argv) {
  if(strcmp(argv, "") == 0) {
    printk("bhai kya kar rha hai tu, konsi led off karu ye to bta?\n");
    return 22;
  }
  
  if(strcmp(argv, " all") == 0) {
    return  LedDriver_TurnAllOff();
  }

  uint32_t index = atoi(argv);
  printk("led index : %d\n", index);
  return LedDriver_TurnOff(index);
}

/* led Toggle command handler */
int Cmd_LedToggleHandler(char * argv) {
  if(strcmp(argv, "") == 0) {
    printk("bhai kya kar rha hai tu, konsi led toggle karu ye to bta?\n");
    return 22;
  }
  
  if(strcmp(argv, " all") == 0) {
    return  LedDriver_TurnAllOpposite();
  }

  uint32_t index = atoi(argv);
  printk("led index : %d\n", index);
  return LedDriver_TurnOpposite(index);
}

/* led IsOn command handler */
int Cmd_LedIsOnHandler(char * argv) {
  if(strcmp(argv, "") == 0) {
    printk("bhai kya kar rha hai tu, konsi led on hai ya nhi ye to bta?\n");
    return 22;
  }
  
  if(strcmp(argv, " all") == 0) {
    return  LedDriver_IsAllOn();
  }

  uint32_t index = atoi(argv);
  printk("led index : %d\n", index);
  return LedDriver_IsOn(index);
}

/* led IsOff command handler */
int Cmd_LedIsOffHandler(char * argv) {
  if(strcmp(argv, "") == 0) {
    printk("bhai kya kar rha hai tu, konsi led off hai ya nhi ye to bta?\n");
    return 22;
  }
  
  if(strcmp(argv, " all") == 0) {
    return  LedDriver_IsAllOff();
  }

  uint32_t index = atoi(argv);
  printk("led index : %d\n", index);
  return LedDriver_IsOff(index);
}


/***********************************  led module command handler's ends  ***********************************/


/*********************************** uart module command handler's starts ***********************************/


/* uart instance create command handler */
int Cmd_UartCreateHandler(char * argv) {
  return UartDriver_Create(&Cmd_uartDev, UART_PORT_0, UART_BAUDRATE_115200);
}

/* uart instance destroy command handler */
int Cmd_UartDestroyHandler(char * argv) {
  return UartDriver_Destroy(&Cmd_uartDev);
}

/* uart tx data command handler */
int Cmd_UartTxHandler(char * argv) {
  char data[CLI_ARG_BUF_SIZE] = "\n\r";

  strcat(data, argv + 1);
  strcat(data, "\n\r\n\r");

  int retVal = UartDriver_TxData(Cmd_uartDev, data, strlen(data), UART_RX_TIMEOUT_MS);
  k_msleep(100);
  return retVal;
}

/* uart tx abort command handler */
int Cmd_UartTxAbortHandler(char * argv) {
  return UartDriver_TxAbort(Cmd_uartDev);
}

/* uart rx enable command handler */
int Cmd_UartRxEnableHandler(char * argv) {
  return UartDriver_RxEnable(Cmd_uartDev, Cmd_uartDevRxBuf, 20, UART_RX_TIMEOUT_MS);
}

/* uart rx disbale command handler */
int Cmd_UartRxDisableHandler(char * argv) {
  return UartDriver_RxDisable(Cmd_uartDev);
}


/***********************************  uart module command handler's ends  ***********************************/