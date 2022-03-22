#include "Cli.h" 
#include "LedDriver/LedDriver.h"
#include <string.h>
#include <sys/printk.h>

const char * ledCmdList[] = {
  "led create",
  "led all on",
  "led all off",
  "led destroy",
};

void parseData(const char * data, const uint32_t dataLen) {
  printk("***** data frame recieved *****\n");
  printk("data : %s\n", data);
  printk("dataLen : %d\n", dataLen);
  printk("***** data frame recieved *****\n\n");
}

void parseCommand(const char * cmd, const uint32_t cmdLen) {
  printk("***** cmd frame recieved *****\n");
  printk("cmd : %s\n", cmd);
  printk("cmdLen : %d\n", cmdLen);
    
  int retVal;

  if(strcmp(cmd, ledCmdList[0]) == 0) {
    retVal = LedDriver_Create();
    printk("LedDriver_Create : %d\n",retVal);
  }
  else if(strcmp(cmd, ledCmdList[1]) == 0) {
    retVal = LedDriver_TurnAllOn();
    printk("LedDriver_TurnAllOn : %d\n",retVal);
  }
  else if(strcmp(cmd, ledCmdList[2]) == 0) {
    retVal = LedDriver_TurnAllOff();
    printk("LedDriver_TurnAllOff : %d\n",retVal);
  }
  else if(strcmp(cmd, ledCmdList[3]) == 0) {
    retVal = LedDriver_Destroy();
    printk("LedDriver_Destroy : %d\n",retVal);
  }
  else {
    printk("Unknown Command !!\n");
  }

  printk("***** cmd frame recieved *****\n\n");

}
