#include "Utils.h"
#include "UartDriver/UartDriver.h"
#include <stdio.h>
#include <string.h>
#include <kernel.h>
#include <sys/printk.h>
#include <drivers/uart.h>

/* bool to check buffer overflow */
bool isUartBuffFull = false;

/* creating an instance of uart data structure for tx & rx */
uartData_t uartTxRx;
uint8_t rxBufTemp[UART_RX_BUF_SIZE] = "";

/* uart thread handle */
extern k_tid_t tid_UartThread;


/*
 * @brief uart event handler. 
 *
 * @details Retrieving the device structure for a uart driver, trasmit a message to let user know
 *          about the uart port along with baudrate and enabling the uart reception.
 *
 * @param uartDev pointer to the uart device structure.
 * @param uartEvt pointer to uart event structure.
 * @param userData pointer to user specified data.
 *
 * @retval APP_SUCCESS If the instance of the uart driver was successfully initialized.
 *                     Otherwise, an error code is returned.
 *
 */
static void UartDriver_UartCallback(const struct device * uartDev, struct uart_event * uartEvt, void * userData)
{
    switch (uartEvt->type)
    {
    case UART_TX_DONE:
        //printk("Hi, I am UART_TX_DONE event\n");
        break;

    case UART_TX_ABORTED:
        //printk("Hi, I am UART_TX_ABORTED event\n");
        break;

    case UART_RX_RDY:
        //printk("Hi, I am UART_RX_RDY event\n");
        if((uartEvt->data.rx.offset) + (uartEvt->data.rx.len) == 256) {
          uartTxRx.rxBufLen = uartEvt->data.rx.len;
          memset(uartTxRx.rxBuf, 0, UART_RX_BUF_SIZE);
          memcpy(uartTxRx.rxBuf, (uartEvt->data.rx.buf + uartEvt->data.rx.offset), uartEvt->data.rx.len);
          isUartBuffFull = true;
        }
        else {
          if(isUartBuffFull) {
            uartTxRx.rxBufLen += uartEvt->data.rx.len;
            strncat(uartTxRx.rxBuf, uartEvt->data.rx.buf, uartEvt->data.rx.len);
            isUartBuffFull = false;
          }
          else {
            uartTxRx.rxBufLen = uartEvt->data.rx.len;
            memset(uartTxRx.rxBuf, 0, UART_RX_BUF_SIZE);
            memcpy(uartTxRx.rxBuf, (uartEvt->data.rx.buf + uartEvt->data.rx.offset), uartEvt->data.rx.len);
          }
          k_thread_resume(tid_UartThread);
        }
        
        break;

    case UART_RX_BUF_REQUEST:
        //printk("Hi, I am UART_RX_BUF_REQUEST event\n");
        uart_rx_buf_rsp(uartDev, rxBufTemp, UART_RX_BUF_SIZE);
        break;

    case UART_RX_BUF_RELEASED:
        //printk("Hi, I am UART_RX_BUF_RELEASED event\n");
        break;

    case UART_RX_DISABLED:
        //printk("Hi, I am UART_RX_DISABLED event\n");
        break;

    case UART_RX_STOPPED:
        //printk("Hi, I am UART_RX_STOPPED event\n");
        break;

    default:
        //printk("Hi, I am defualt case\n");
        break;
    }
}

/*
 * @brief Function for generate the start-up message. 
 *
 *
 * @param uartAddress pointer to the uart device structure.
 * @param uartBaurate uart baudrate.
 *
 * @retval APP_SUCCESS If the respective uart baudrate was setted successfully.
 *                     Otherwise, an error code is returned.
 */
static int uartBaudrateSet(const struct device * uartAddress, uint32_t uartBaudrate) {
  int errCode;
  struct uart_config uartConfig;

  uartConfig.baudrate  = (uint32_t) uartBaudrate;
  uartConfig.parity    = (uint8_t)  UART_CFG_PARITY_NONE;
  uartConfig.stop_bits = (uint8_t)  UART_CFG_STOP_BITS_1;
  uartConfig.data_bits = (uint8_t)  UART_CFG_DATA_BITS_8;
  uartConfig.flow_ctrl = (uint8_t)  UART_CFG_FLOW_CTRL_NONE;
  
  errCode = uart_configure(uartAddress, &uartConfig);
  VERIFY_SUCCESS(errCode);

  return APP_SUCCESS;
}

/*
 * @brief Function for generate the start-up message. 
 *
 *
 * @param message pointer to message buffer.
 * @param portStr pointer to uart port buffer.
 * @param baudrate uart baurate.
 *
 * @retval None.
 *
 */
static void formMessage(char * message, char * portStr, uint32_t baudrate) {
  char baudrateStr[10] = "";
  sprintf(baudrateStr, "%d", baudrate);

  strcat(message,portStr);
  strcat(message," port initialized with baudrate ");
  strcat(message,baudrateStr);
  strcat(message,"\n\r");
}

/*
 * @brief Function for creating an instance of uart driver. 
 *
 * @details Retrieving the device structure for a uart driver, trasmit a message to let user know
 *          about the uart port along with baudrate and enabling the uart reception.
 *
 * @param None
 *
 * @retval APP_SUCCESS If the instance of the uart driver was successfully initialized.
 *                     Otherwise, an error code is returned.
 *
 */
int UartDriver_Create(const struct device ** uartAddress, uint32_t uartPort, uint32_t uartBaudrate) {
  int errCode;
  char portNum[1] = "X";
  char portStr[10] = "";
  
  /* make uart port string from respective uart port */
  strcat(portStr,"UART_");
  sprintf(portNum, "%d", uartPort);
  strcat(portStr,portNum);
  
  /* retrieve the device structure for a respective uart port and verify the same  */
  *uartAddress = device_get_binding(portStr);
  VERIFY_PARAM_NOT_NULL(*uartAddress);
  
  /* set the event handler for respective uart port */
  errCode = uart_callback_set(*uartAddress, UartDriver_UartCallback, NULL);
  VERIFY_SUCCESS(errCode);

  /* configure the uart as per the requested baudrate */
  errCode = uartBaudrateSet(*uartAddress, uartBaudrate);
  VERIFY_SUCCESS(errCode);

  /* enable the uart reception into respective buffer */
  errCode = uart_rx_enable(*uartAddress, rxBufTemp, UART_RX_BUF_SIZE, UART_RX_TIMEOUT_MS);
  VERIFY_SUCCESS(errCode);
  
  char message[50] = ""; 
  formMessage(message, portStr, uartBaudrate);

  uartTxRx.txBufLen = strlen(message);
  for(int i=0; i<uartTxRx.txBufLen; i++) {
    uartTxRx.txBuf[i] = message[i];
  }
  
  /* transmit the respective buffer through uart */
  //errCode = uart_tx(*uartAddress, uartTxRx.txBuf, uartTxRx.txBufLen, UART_RX_TIMEOUT_MS);
  //VERIFY_SUCCESS(errCode);
  
  return APP_SUCCESS;
}

/*
 * @brief Function for destroying an instance of uart driver. 
 *
 * @details Releasing the device structure for a uart driver, aborting ongoing transmittion
 *          and disabling the uart reception.
 *
 * @param None
 *
 * @retval APP_SUCCESS If the instance of the uart driver was successfully de-initialized.
 *                     Otherwise, an error code is returned.
 *
 */
int UartDriver_Destroy(const struct device ** uartAddress) {
  /* validate the uart dev pointer */
  VERIFY_PARAM_NOT_NULL(*uartAddress);

  /* abort the current uart transmition, if any */
  uart_tx_abort(*uartAddress);
  
  /* disable the uart reception, if any */
  uart_rx_disable(*uartAddress);
  
  /* release the device structure for a uart driver and verify the same */
  *uartAddress = NULL;
  VERIFY_PARAM_IS_NULL(*uartAddress); 

  return APP_SUCCESS;
}

/*
 * @brief Function for transmit the respective buffer through uart.
 *
 * @param uartAddress pointer to the uart device structure.
 *
 * @retval APP_SUCCESS If the respective buffer was transmitted successfully through uart. 
 *         Otherwise, an error code is returned.
 *
 */
int UartDriver_TxData(const struct device * uartAddress, uint8_t * txBuf, uint32_t txBufLen, int32_t timeout) {
  int errCode;

  /* validate the uart dev pointer */
  VERIFY_PARAM_NOT_NULL(uartAddress);
  
  /* validate the uart transmition buffer pointer */
  VERIFY_PARAM_NOT_NULL(txBuf);
  
  /* transmit the respective buffer through uart */
  errCode = uart_tx(uartAddress, txBuf, txBufLen, timeout);
  VERIFY_SUCCESS(errCode);

  return APP_SUCCESS;
}

/*
 * @brief Function for aborting the ongoing uart transmission.
 *
 * @param uartAddress pointer to the uart device structure.
 *
 * @retval APP_SUCCESS If the ongoing uart transmittion was aborted successfully. 
 *         Otherwise, an error code is returned.
 *
 */
int UartDriver_TxAbort(const struct device * uartAddress) {
  int errCode;

  /* validate the uart dev pointer */
  VERIFY_PARAM_NOT_NULL(uartAddress);
  
  /* abort the current uart transmition */
  errCode = uart_tx_abort(uartAddress);
  VERIFY_SUCCESS(errCode);

  return APP_SUCCESS;
}

/*
 * @brief Function for enabling the uart reception into respective buffer.
 *
 * @param uartAddress pointer to the uart device structure.
 *
 * @retval APP_SUCCESS If the uart reception was enabled successfully into respective buffer. 
 *         Otherwise, an error code is returned.
 *
 */
int UartDriver_RxEnable(const struct device * uartAddress, uint8_t * rxBuf, uint32_t rxBufLen, int32_t timeout) {
  int errCode;
  
  /* validate the uart dev pointer */
  VERIFY_PARAM_NOT_NULL(uartAddress); 

  /* validate the uart receive buffer pointer */
  VERIFY_PARAM_NOT_NULL(rxBuf);
  
  /* enable the uart reception into respective buffer */
  errCode = uart_rx_enable(uartAddress, rxBuf, rxBufLen, timeout);
  VERIFY_SUCCESS(errCode);

  return APP_SUCCESS;
}

/*
 * @brief Function for disabling the uart reception.
 *
 * @param uartAddress pointer to the uart device structure.
 *
 * @retval APP_SUCCESS If the uart reception was disabled successfully. 
 *         Otherwise, an error code is returned.
 *
 */
int UartDriver_RxDisable(const struct device * uartAddress) {
  int errCode;

  /* validate the uart dev pointer */
  VERIFY_PARAM_NOT_NULL(uartAddress); 
  
  /* disable the uart reception */
  errCode = uart_rx_disable(uartAddress);
  VERIFY_SUCCESS(errCode);

  return APP_SUCCESS;
}