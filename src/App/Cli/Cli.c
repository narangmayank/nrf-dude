#include "Cli/Cli.h"
#include "LedDriver/LedDriver.h"
#include <stdlib.h>
#include <string.h>
#include <sys/printk.h>

bool isCliMode = false;
uint8_t cliStartFrame[] = "hi bhai";
uint8_t cliStopFrame[] = "bye bhai";

int shellLedCreateHandler(int argc, char * argv) {
  return LedDriver_Create();
}

int shellLedDestroyHandler(int argc, char * argv) {
  return LedDriver_Destroy();
}

int shellLedAllOnHandler(int argc, char * argv) {
  return LedDriver_TurnAllOn();
}

int shellLedAllOffHandler(int argc, char * argv) {
  return LedDriver_TurnAllOff();
}

int shellLedOnHandler(int argc, char * argv) {
  uint32_t index = atoi(argv);
  printk("led index : %d\n", index);
  return LedDriver_TurnOn(index);
}

int shellLedOffHandler(int argc, char * argv) {
  uint32_t index = atoi(argv);
  printk("led index : %d\n", index);
  return LedDriver_TurnOff(index);
}

int shellLedToggleHandler(int argc, char * argv) {
  uint32_t index = atoi(argv);
  printk("led index : %d\n", index);
  return LedDriver_TurnOpposite(index);
}

/* filling the led commands */
static const ShellCommands_t ledCmdList[] = {
  {"led create" , shellLedCreateHandler , "create an instance of an led" },
  {"led destroy", shellLedDestroyHandler, "destroy an instance of an led"},
  {"led all on" , shellLedAllOnHandler  , "turn on all led's"},
  {"led all off", shellLedAllOffHandler , "turn off all led's"},
  {"led on"     , shellLedOnHandler     , "turn on resoective led"},
  {"led off"    , shellLedOffHandler    , "turn off resoective led"},
  {"led toggle" , shellLedToggleHandler , "toggle resoective led"}
};

static const int ledCmdListLen = sizeof(ledCmdList)/sizeof(ledCmdList[0]);

void Cli_Create() {
  isCliMode = true;
  printk("Cli Created !!\n");
  printk("cmd start frame found, switching to cmd mode !!\n\n");

  //for(int i=0; i<ledCmdListLen; i++) {
  //  strcpy(cliCmdList[i].cmd, ledCmdList[i].cmd);
  //  strcpy(cliCmdList[i].apiName, ledCmdList[i].apiName);
  //  cliCmdList[i].api = ledCmdList[i].api;
  //  strcpy(cliCmdList[i].desc, ledCmdList[i].desc);
  //}
}

void Cli_Destroy() {
  isCliMode = false;
  printk("Cli Destroyed !!\n");
  printk("cmd stop frame found, switching to data mode !!\n\n");

  //for(int i=0; i<ledCmdListLen; i++) {
  //  strcpy(cliCmdList[i].cmd, ledCmdList[i].cmd);
  //  strcpy(cliCmdList[i].apiName, ledCmdList[i].apiName);
  //  cliCmdList[i].api = ledCmdList[i].api;
  //  strcpy(cliCmdList[i].desc, ledCmdList[i].desc);
  //}
}


