#ifndef A_UartThread_H
#define A_UartThread_H


/* arguments to entry point of the cli thread */
#define ARG_1 10
#define ARG_2 20
#define ARG_3 30

/* cli thread priority */
#define UART_THREAD_PRIORITY 1

/* cli thread stack size */
#define UART_THREAD_STACK_SIZE 1024

/* declares the entry point of the thread */
void UartThread(void * arg1, void * arg2, void * arg3);


/* function prototypes starts */

void printRecievedFrame();
void parseRecievedFrame();
void parseDataFrame(const char * dataFrame, const uint32_t dataFrameLen);
void parseCommandFrame(const char * cmdFrame, const uint32_t cmdFrameLen);

/* function prototypes ends */


#endif /* A_UartThread_H */