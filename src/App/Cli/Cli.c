#include "Utils.h"
#include "Cli/Cli.h"
#include "Cli/CmdHandler.h"
#include "UartDriver/UartDriver.h"
#include <stdio.h>
#include <string.h>
#include <kernel.h>
#include <sys/printk.h>

// Cli buffer's
char cliCmdBuf[CLI_CMD_BUF_SIZE] = "";
char cliArgBuf[CLI_ARG_BUF_SIZE] = "";
char cliResBuf[CLI_RES_BUF_SIZE] = "";  

// Cli variables
bool isCliMode = false;
uint8_t cliStartFrame[] = "hye dude";
uint8_t cliStopFrame[] = "bye dude";

// Cli messages
uint8_t cliPrompt[] = "\nnrf-dude>$";
uint8_t cliSuccessMsg[] = "Executed! (err_code : %d)\n";
uint8_t cliFailureMsg[] = "Error! (Unknown Command)\n";
uint8_t cliExitMsg[] = "Thanks, Bye dude!\n\n$";

/* Cli command's */
static const CliCommands_t cliCmdList[] = {
  {"help me", NULL, "", ""},

  {"run unit tests"     , Cmd_UnitTestsHandler    , "\nrun unit tests"   , " run entire unit tests suite"},
  {"run led unit tests" , Cmd_LedUnitTestsHandler , "run led unit tests" , "run only led unit tests suite"},
  {"run uart unit tests", Cmd_UartUnitTestsHandler, "run uart unit tests", "run only uart unit tests suite\n"},

  {"led peripheral init" , Cmd_LedCreateHandler , "led peripheral init"  , "create an instance of led driver"},
  {"led peripheral deinit", Cmd_LedDestroyHandler, "led peripheral deinit" , "destroy the instance of led driver"},
  {"led on "             , Cmd_LedOnHandler     , "led on : led_index"     , "turn on user specified led"},
  {"led off "            , Cmd_LedOffHandler    , "led off : led_index"    , "turn off user specified led"},
  {"led toggle "         , Cmd_LedToggleHandler , "led toggle : led_index" , "toggle user specified led"},
  // {"is led on "         , Cmd_LedIsOnHandler   , "is led on : led_index" , "is user specified led on"},
  // {"is led off "        , Cmd_LedIsOffHandler  , "is led off : led_index", "is user specified led off\n"},

  {"uart peripheral init"  , Cmd_UartCreateHandler   , "uart peripheral init"  , "create an instance of uart driver"},
  {"uart peripheral deinit", Cmd_UartDestroyHandler  , "uart peripheral deinit", "destroy the instance of uart driver"},
  {"uart tx "              , Cmd_UartTxHandler       , "uart tx : data_to_send", "transmit user specified data from uart"},
  {"uart tx abort"         , Cmd_UartTxAbortHandler  , "uart tx abort"         , "abort current uart transmission"},
  {"uart rx enable"        , Cmd_UartRxEnableHandler , "uart rx enable"        , "enable uart reception"},
  {"uart rx disable"       , Cmd_UartRxDisableHandler, "uart rx disable"       , "disable uart reception"}
};

static const int cliCmdListLen = sizeof(cliCmdList)/sizeof(cliCmdList[0]);


/* uart driver instance */
extern const struct device * uartDev_2;

/* seperate command and arguments from the recived command frane */
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

/* If cmd found then execute it otherwise move on and prepare the response message
 * based on the whats going on here 
 */
static void doSomething() {
  int retVal;
  char buff[3];
  bool isCmdFound = false;
  
  /* clear the cli response buffer */
  memset(cliResBuf, 0x00, CLI_RES_BUF_SIZE);
  
  /* If user is asking for help, list all the available commands along with the
   * use case and just return
   */
  if(strcmp(cliCmdBuf, cliCmdList[0].cmd) == 0) {
    /* loop over all the available commands and get the description in response buffer */
    for(int i=1; i<cliCmdListLen; i++) {
      
      /* how much spaces needed for clear visualization */
      uint32_t len = 50 - strlen(cliCmdList[i].cmdFrame) + 5; 

      // generate the space buffer to be appended at the last to get clear visualization
      char spaceBuff[50] = "";
      memset(spaceBuff, 0x20, len);
      
      /* clear the cli response buffer */
      memset(cliResBuf, 0x00, CLI_RES_BUF_SIZE);

      // prepare response buffer
      strcat(cliResBuf, cliCmdList[i].cmdFrame);
      strncat(cliResBuf, spaceBuff, len);
      strcat(cliResBuf, cliCmdList[i].cmdDesc);
      strcat(cliResBuf, "\n");

      /* give response to user */
      Cli_Respond(cliResBuf, strlen(cliResBuf));

      /* wait for previous response to be sended completely */
      k_msleep(10);
    }
    
    /* clear the cli response buffer */
    memset(cliResBuf, 0x00, CLI_RES_BUF_SIZE);

    /* keeping the cli prompt for next cmd */
    strcpy(cliResBuf, cliPrompt);

    return;
  }

  /* If user is not asking for help but still given some command then just loop over all the available
   * commands, If matches to any command then call the respective handler, set the flag and break the looping. 
   */
  for(int i=1; i<cliCmdListLen; i++) {
    if(strcmp(cliCmdBuf, cliCmdList[i].cmd) == 0) {
      /* oh, cmd found ! */
      retVal = (cliCmdList[i].handler)(cliArgBuf);

      /* give logs in debug terminal */
      printk("Executed! (err_code : %d)\n", retVal);

      /* generate response for this cmd */    
      int tempVal = snprintf(cliResBuf, CLI_RES_BUF_SIZE, cliSuccessMsg, retVal);

      if(tempVal >= CLI_RES_BUF_SIZE) {
        printk("Cli Response Buffer Truncated.\n");
      }

      /* set this bool to get info about cmd found */
      isCmdFound = true;

      break;
    }
  }
  
  /* If command is not found then let user know about it */
  if(!isCmdFound) {
    /* oh no, seems like user has done mistake while typing ! */

    /* give logs in debug terminal */
    printk("Error! (Unknown Command)\n");

    /* generate response for cmd not found */
    memcpy(cliResBuf, cliFailureMsg, strlen(cliFailureMsg));
  }
  
  /* keeping the cli prompt for next cmd */
  strcat(cliResBuf, cliPrompt);
}

/* Create the instance of Cli */
void Cli_Create() {
  isCliMode = true;
  printk("Cli Created !!\n\n");
  Cli_Respond(cliPrompt, strlen(cliPrompt));
}

/* Destroy the instance of Cli */
void Cli_Destroy() {
  isCliMode = false;
  printk("Cli Destroyed !!\n\n");
  Cli_Respond(cliExitMsg, strlen(cliExitMsg));
}

/* Process the recieved command frame */
void Cli_Process(const char * cmdFrame, const uint32_t cmdFrameLen) {  
  /* fill cli cmd buf and arg buf */
  getCliBuf(cmdFrame, cmdFrameLen);

  /* do something */
  doSomething();  

  /* give response to user after doing something */
  Cli_Respond(cliResBuf, strlen(cliResBuf));
}

/* Give the reponse for the command */
void Cli_Respond(const char * resFrame, const uint32_t resFrameLen) {
  int errCode;

  errCode = UartDriver_TxData(uartDev_2, resFrame, resFrameLen, UART_RX_TIMEOUT_MS);
  VERIFY_SUCCESS(errCode);
}