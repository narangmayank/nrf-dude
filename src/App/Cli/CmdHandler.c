#include "Cli/CmdHandler.h" 
#include "LedDriver/LedDriver.h"
#include <string.h>
#include <stdlib.h>
#include <sys/printk.h>

int Cmd_LedCreateHandler(char * argv) {
  return LedDriver_Create();
}

int Cmd_LedDestroyHandler(char * argv) {
  return LedDriver_Destroy();
}

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

int Cmd_LedToggleHandler(char * argv) {
  if(strcmp(argv, "") == 0) {
    printk("bhai kya kar rha hai tu, konsi led off karu ye to bta?\n");
    return 22;
  }
  
  if(strcmp(argv, " all") == 0) {
    return  LedDriver_TurnAllOpposite();
  }

  uint32_t index = atoi(argv);
  printk("led index : %d\n", index);
  return LedDriver_TurnOpposite(index);
}