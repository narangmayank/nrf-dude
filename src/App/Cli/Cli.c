#include "Utils.h"
#include "Cli/Cli.h"
#include "Cli/CmdHandler.h"
#include "UartDriver/UartDriver.h"
#include <string.h>
#include <sys/printk.h>

char cliCmdBuf[CLI_CMD_BUF_SIZE] = "";
char cliArgBuf[CLI_ARG_BUF_SIZE] = "";
char cliResBuf[CLI_RES_BUF_SIZE] = "";  

bool isCliMode = false;
uint8_t cliStartFrame[] = "hi bhai";
uint8_t cliStopFrame[] = "bye bhai";

uint8_t cliPrompt[] = "\nnrf-bhai>$";
uint8_t cliSuccessMsg[] = "Shandaar Bhai\n";
uint8_t cliFailureMsg[] = "Arre Bhai Bhai Bhai !!!\n";
uint8_t cliExitMsg[] = "acha chalta hu duaoo me yad rkhna!\n\n$";

/* cli commands */
static const CliCommands_t cliCmdList[] = {
  {"unit tests run kar bhai"      , Cmd_UnitTestsHandler , "run the pre defined unit tests"},
  {"led instance create kar bhai" , Cmd_LedCreateHandler , "create an instance of an led driver"},
  {"led instance destroy kar bhai", Cmd_LedDestroyHandler, "destroy an instance of an led driver"},
  {"led on kar bhai "             , Cmd_LedOnHandler     , "turn on respective led"},
  {"led off kar bhai "            , Cmd_LedOffHandler    , "turn off respective led"},
  {"led toggle kar bhai "         , Cmd_LedToggleHandler , "toggle respective led"},
  {"led on hai kya bhai "         , Cmd_LedIsOnHandler   , "is respective led on"},
  {"led off hai kya bhai "        , Cmd_LedIsOffHandler  , "is respective led off"}
};

static const int cliCmdListLen = sizeof(cliCmdList)/sizeof(cliCmdList[0]);


/* uart driver instance */
extern const struct device * uartDev_2;


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
  
  memset(cliResBuf, 0x00, CLI_RES_BUF_SIZE);

  /* loop over all the led commands, If matches to any available command then call the
   * respective handler, set the flag and break the looping. 
   */
  for(int i=0; i<cliCmdListLen; i++) {
    if(strcmp(cliCmdBuf, cliCmdList[i].cmd) == 0) {
      retVal = (cliCmdList[i].handler)(cliArgBuf);
      printk("Shandaar bhai\n");
      printk("retVal : %d\n", retVal);
      memcpy(cliResBuf, cliSuccessMsg, strlen(cliSuccessMsg));
      isCmdFound = true;
      break;
    }
  }

  /* If command is not found then let user know about it */
  if(!isCmdFound) {
    printk("Arre Bhai Bhai Bhai !!!\n");
    printk("> kya kar rha hai tu??... Unknown Command\n");
    memcpy(cliResBuf, cliFailureMsg, strlen(cliFailureMsg));
  }

  strcat(cliResBuf, cliPrompt);
}

void Cli_Create() {
  isCliMode = true;
  printk("Cli Created !!\n\n");
  Cli_Respond(cliPrompt, strlen(cliPrompt));
}

void Cli_Destroy() {
  isCliMode = false;
  printk("Cli Destroyed !!\n\n");
  Cli_Respond(cliExitMsg, strlen(cliExitMsg));
}

void Cli_Process(const char * cmdFrame, const uint32_t cmdFrameLen) {  
  /* fill cli cmd buf and arg buf */
  getCliBuf(cmdFrame, cmdFrameLen);

  /* do something */
  doSomething();  

  /* kidnly keep the cli prompt for next cmd */
  Cli_Respond(cliResBuf, strlen(cliResBuf));
}

void Cli_Respond(const char * resFrame, const uint32_t resFrameLen) {
  int errCode;

  errCode = UartDriver_TxData(uartDev_2, resFrame, resFrameLen, UART_RX_TIMEOUT_MS);
  VERIFY_SUCCESS(errCode);
}