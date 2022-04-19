#ifndef A_CmdHandler_H
#define A_CmdHandler_H

/* function prototypes starts */


// unit tests command handler's
int Cmd_UnitTestsHandler(char *argv);

// led module command handler's
int Cmd_LedCreateHandler(char * argv);
int Cmd_LedDestroyHandler(char * argv);
int Cmd_LedOnHandler(char * argv);
int Cmd_LedOffHandler(char * argv);
int Cmd_LedToggleHandler(char * argv);
int Cmd_LedIsOnHandler(char * argv);
int Cmd_LedIsOffHandler(char * argv);

// uart module command handler's
int Cmd_UartCreateHandler(char * argv);
int Cmd_UartDestroyHandler(char * argv);
int Cmd_UartTxHandler(char * argv);
int Cmd_UartTxAbortHandler(char * argv);
int Cmd_UartRxEnableHandler(char * argv);
int Cmd_UartRxDisableHandler(char * argv);


/* function prototypes ends */

#endif /* A_CmdHandler_H */
