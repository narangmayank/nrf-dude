#ifndef D_UartDriver_H
#define D_UartDriver_H

#include <stdint.h>
#include <device.h>

#define UART_NUMBER 1
#define UART_RX_BUF_SIZE 256
#define UART_RX_TIMEOUT_MS 50

typedef enum {
  UART_PORT_0 = 0,
  UART_PORT_1 = 1,
  UART_PORT_2 = 2,
  UART_PORT_3 = 3
} uartPort_t;

typedef enum {
  UART_BAUDRATE_9600 = 9600,
  UART_BAUDRATE_115200 = 115200
} uartBaudrate_t;

typedef struct {
  uint8_t txBuf[UART_RX_BUF_SIZE + 1];
  uint32_t txBufLen;
  uint8_t rxBuf[UART_RX_BUF_SIZE + 1];
  uint32_t rxBufLen;
} uartData_t;


int UartDriver_Create(const struct device ** uartAddress, uint32_t uartPort, uint32_t uartBaudrate);
int UartDriver_Destroy(const struct device ** uartAddress);

int UartDriver_TxData(const struct device * uartAddress, uint8_t * buf, uint32_t bufLen, int32_t timeout);
int UartDriver_TxAbort(const struct device * uartAddress);
int UartDriver_RxEnable(const struct device * uartAddress, uint8_t * buf, uint32_t bufLen, int32_t timeout);
int UartDriver_RxDisable(const struct device * uartAddress);

#endif /* D_UartDriver_H */
