#ifndef A_CmdHandler_H
#define A_CmdHandler_H

/* function prototypes starts */

int Cmd_UnitTestsHandler(char *argv);

int Cmd_LedCreateHandler(char * argv);
int Cmd_LedDestroyHandler(char * argv);
int Cmd_LedOnHandler(char * argv);
int Cmd_LedOffHandler(char * argv);
int Cmd_LedToggleHandler(char * argv);
int Cmd_LedIsOnHandler(char * argv);
int Cmd_LedIsOffHandler(char * argv);

/* function prototypes ends */

#endif /* A_CmdHandler_H */
