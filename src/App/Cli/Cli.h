#ifndef A_Cli_H
#define A_Cli_H

#include <stdint.h>

#define CLI_CMD_BUF_SIZE 50        // CLI Command Buffer Size
#define CLI_ARG_BUF_SIZE 50        // CLI Argument Buffer Size
#define CLI_RES_BUF_SIZE 100       // CLI Response Buffer Size

/* data structure to represnt the cmd properties */
typedef struct {
  const char * cmd;
  int (*handler)(char * argv);
  const char * desc;
} CliCommands_t; 

/* function prototypes starts */

void Cli_Create();
void Cli_Destroy();
void Cli_Process(const char * cmdFrame, const uint32_t cmdFrameLen);
void Cli_Respond(const char * resFrame, const uint32_t resFrameLen);

/* function prototypes ends */


#endif /* A_Cli_H */
