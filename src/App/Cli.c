#include "Cli.h" 
#include "LedDriver/LedDriver.h"
#include <string.h>
#include <sys/printk.h>

/* filling the led commands */
static const ledCmd_t ledCmdList[] = {
  {"led create" , "LedDriver_Create()"    , LedDriver_Create    , "create an instance of an led"},
  {"led all on" , "LedDriver_TurnAllOn()" , LedDriver_TurnAllOn , "turn on all the led's"},
  {"led all off", "LedDriver_TurnAllOff()", LedDriver_TurnAllOff, "turn off all the led's"},
  {"led destroy", "LedDriver_Destroy()"   , LedDriver_Destroy   , "destroy an instance of an led"},
};

static const int ledCmdListLen = sizeof(ledCmdList)/sizeof(ledCmdList[0]);

/* I will parse the incoming data */
void parseData(const char * data, const uint32_t dataLen) {
  printk("***** data frame recieved *****\n");
  printk("data : %s\n", data);
  printk("dataLen : %d\n", dataLen);
  printk("***** data frame recieved *****\n\n");
}

/* Iwill parse the incoming command */
void parseCommand(const char * cmd, const uint32_t cmdLen) {
  printk("***** cmd frame recieved *****\n");
  printk("cmd : %s\n", cmd);
  printk("cmdLen : %d\n", cmdLen);
    
  int retVal;
  bool isCmdFound = false;
  
  /* loop over all the led commands, If matches to any available command then call the
   * respective api using function pointer and set the flag and break the looping 
   */
  for(int i=0; i<ledCmdListLen; i++) {
    if(strcmp(cmd, ledCmdList[i].cmd) == 0) {
      retVal = (ledCmdList[i].api)();
      printk("%s : %d\n",ledCmdList[i].apiName, retVal);
      isCmdFound = true;
      break;
    }
  }

  /* If command is not found then let user know about it */
  if(!isCmdFound) {
    printk("Unknown Command\n");
  }

  printk("***** cmd frame recieved *****\n\n");
}
