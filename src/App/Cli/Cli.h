#ifndef A_Cli_H
#define A_Cli_H

#include <stdint.h>

/* data structure to represnt the cmd properties */
typedef struct {
  const char * cmd;
  int (*handler)(int argc, char * argv);
  const char * desc;
} ShellCommands_t; 

/* function prototypes starts */

void Cli_Create();
void Cli_Destroy();

/* function prototypes ends */


#endif /* A_Cli_H */
