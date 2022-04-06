#include "Cli/Cli.h"
#include "Cli/CmdHandler.h"
#include <string.h>
#include <sys/printk.h>

char cliCmdBuf[CLI_CMD_BUF_SIZE] = "";
char cliArgBuf[CLI_ARG_BUF_SIZE] = "";

bool isCliMode = false;
uint8_t cliStartFrame[] = "hi bhai";
uint8_t cliStopFrame[] = "bye bhai";

/* led module commands */
static const CliCommands_t ledCmdList[] = {
  {"led instance create kar bhai" , Cmd_LedCreateHandler , "create an instance of an led driver"},
  {"led instance destroy kar bhai", Cmd_LedDestroyHandler, "destroy an instance of an led driver"},
  {"led on kar bhai "             , Cmd_LedOnHandler     , "turn on respective led"},
  {"led off kar bhai "            , Cmd_LedOffHandler    , "turn off respective led"},
  {"led toggle kar bhai "         , Cmd_LedToggleHandler , "toggle respective led"}
};

static const int ledCmdListLen = sizeof(ledCmdList)/sizeof(ledCmdList[0]);

static void getCliBuf(const char * cmdFrame, const uint32_t cmdFrameLen) {
  /* clear the cli cmd buffer and cli argument buffer */
  memset(cliCmdBuf, 0x00, CLI_CMD_BUF_SIZE);
  memset(cliArgBuf, 0x00, CLI_ARG_BUF_SIZE);

  /* loop over the cmd frame and keep collecting data in cli cmd buffer until you
   * not met ':' , once you met this guy then start collecting data in cli arg buffer
   * ':' --> this is the seperator between command and arguments 
   */
  int wtIndex = 0;
  char * ptr = cliCmdBuf;
  for(int i=0; i<cmdFrameLen; i++) {
    if(cmdFrame[i] == ':') {
      wtIndex = 0;
      ptr = cliArgBuf;
      continue;
    }
    ptr[wtIndex++] = cmdFrame[i];
  }

  printk("cliCmdBuf : %s\n", cliCmdBuf);
  printk("cliArgBuf : %s\n", cliArgBuf);
}

static void doSomething() {
  int retVal;
  bool isCmdFound = false;
  
  /* loop over all the led commands, If matches to any available command then call the
   * respective handler, set the flag and break the looping. 
   */
  for(int i=0; i<ledCmdListLen; i++) {
    if(strcmp(cliCmdBuf, ledCmdList[i].cmd) == 0) {
      retVal = (ledCmdList[i].handler)(cliArgBuf);
      printk("Shandaar bhai\n");
      printk("retVal : %d\n", retVal);
      isCmdFound = true;
      break;
    }
  }

  /* If command is not found then let user know about it */
  if(!isCmdFound) {
    printk("Arre Bhai Bhai Bhai !!!\n");
    printk("> kya kar rha hai tu??... Unknown Command\n");
  }
}

void Cli_Create() {
  isCliMode = true;
  printk("Cli Created !!\n\n");
}

void Cli_Destroy() {
  isCliMode = false;
  printk("Cli Destroyed !!\n\n");
}

void Cli_Process(const char * cmdFrame, const uint32_t cmdFrameLen) {  
  /* fill cli cmd buf and arg buf */
  getCliBuf(cmdFrame, cmdFrameLen);

  /* do something */
  doSomething();  
}