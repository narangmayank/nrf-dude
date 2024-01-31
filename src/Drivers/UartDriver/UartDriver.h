#ifndef D_UartDriver_H
#define D_UartDriver_H

#include <stdint.h>
#include <zephyr/device.h>

#define UART_NUMBER                   1         // number of active uart ports
#define UART_RX_BUF_SIZE              256       // uart reception buffer size
#define UART_RX_TIMEOUT_MS  (int32_t) 50        // time between 2 uart reception in ms

/* enum to specify the uart ports */
typedef enum {
  UART_PORT_0 = 0,
  UART_PORT_1 = 1,
  UART_PORT_2 = 2,
  UART_PORT_3 = 3
} uartPort_t;

/* enum to specify the standard baudrates */
typedef enum {
  UART_BAUDRATE_9600 = 9600,
  UART_BAUDRATE_115200 = 115200
} uartBaudrate_t;

/* data structure to represent uart tx rx buffers along with thier respective length */
typedef struct {
  uint8_t txBuf[UART_RX_BUF_SIZE + 1];
  uint32_t txBufLen;
  uint8_t rxBuf[UART_RX_BUF_SIZE + 1];
  uint32_t rxBufLen;
} uartData_t;

/* function prototypes start */

int UartDriver_Create(const struct device ** uartAddress, uint32_t uartPort, uint32_t uartBaudrate);
int UartDriver_Destroy(const struct device ** uartAddress);

int UartDriver_TxData(const struct device * uartAddress, uint8_t * buf, uint32_t bufLen, int32_t timeout);
int UartDriver_TxAbort(const struct device * uartAddress);
int UartDriver_RxEnable(const struct device * uartAddress, uint8_t * buf, uint32_t bufLen, int32_t timeout);
int UartDriver_RxDisable(const struct device * uartAddress);

/* function prototypes ends */

#endif /* D_UartDriver_H */
