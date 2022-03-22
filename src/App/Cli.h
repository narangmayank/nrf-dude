#ifndef A_Cli_H
#define A_Cli_H


#include <stdint.h>

/* data structure to represnt the cmd properties */
typedef struct {
  const char * cmd;
  const char * apiName;
  int (*api)();
  const char * desc;
} ledCmd_t; 

/* function prototypes starts */

void parseData(const char * data, const uint32_t dataLen);
void parseCommand(const char * cmd, const uint32_t cmdLen);

/* function prototypes ends */


#endif /* A_Cli_H */
