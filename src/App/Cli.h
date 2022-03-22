#ifndef A_Cli_H
#define A_Cli_H

#include <stdint.h>

void parseData(const char * data, const uint32_t dataLen);
void parseCommand(const char * cmd, const uint32_t cmdLen);

#endif /* A_Cli_H */
