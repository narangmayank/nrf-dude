#include "Utils.h"
#include "DriveDriver.h" 
#include "LedDriver/LedDriver.h" 
#include "UartDriver/UartDriver.h"
#include <kernel.h>

/*
 * @brief Function for verifying the led driver and inturn showing the usage to the user.
 *
 * @details We are calling each API of the led driver in some order to show something
 *          meaningfull and validating the API at the same time
 *
 * @param None.
 *
 * @retval APP_SUCCESS If the of the led driver was verified successfully.
 *                     Otherwise, an error code is returned.
 *
 */
int driveLed() {
  int errCode;

  /* creating an instance of led driver */
  errCode = LedDriver_Create();
  VERIFY_SUCCESS(errCode);
    
  /* utilizing led turn on api's */
  for(uint32_t i=0; i<4; i++) {
    errCode = LedDriver_TurnOn(i);
    VERIFY_SUCCESS(errCode);
  }
    
  k_msleep(2000);
  
  /* utilizing led turn off api's */
  for(uint32_t i=0; i<4; i++) {
    errCode = LedDriver_TurnOff(i);
    VERIFY_SUCCESS(errCode);
  }

  k_msleep(2000);
  
  /* utilizing led turn all on api */
  errCode = LedDriver_TurnAllOn();
  VERIFY_SUCCESS(errCode);

  k_msleep(2000);
  
  /* utilizing led turn all of api */
  errCode = LedDriver_TurnAllOff();
  VERIFY_SUCCESS(errCode);

  k_msleep(2000);
  
  /* utilizing led turn opposite api's */
  for(uint32_t i=0; i<4; i++) {
    errCode = LedDriver_TurnOpposite(i);
    VERIFY_SUCCESS(errCode);
  }
  
  k_msleep(2000);

  /* destroying an instance of led driver */
  errCode = LedDriver_Destroy();
  VERIFY_SUCCESS(errCode);

  return APP_SUCCESS;
}

/*
 * @brief Function for verifying the uart driver and inturn showing the usage to the user.
 *
 * @details We are calling each API of the uart driver in some order to show something
 *          meaningfull and validating the API at the same time
 *
 * @param None.
 *
 * @retval APP_SUCCESS If the of the uart driver was verified successfully.
 *                     Otherwise, an error code is returned.
 *
 */
int driveUart() {
  int errCode;
  uint8_t rxBuf[20] = "";
  uint8_t txBuf[20] = "I am UART_0 buffer\n\r";
  const struct device * driveUartDev = NULL;
  
  /* creating an instance of uart driver */
  errCode = UartDriver_Create(&driveUartDev, UART_PORT_0, UART_BAUDRATE_115200);
  VERIFY_SUCCESS(errCode);
  
  k_msleep(2000);
  
  /* utilizing uart transmit api */
  errCode = UartDriver_TxData(driveUartDev, txBuf, 20, UART_RX_TIMEOUT_MS);
  VERIFY_SUCCESS(errCode);
  
  k_msleep(2000);

  /* utilizing uart transmit abort api */
  errCode = UartDriver_TxData(driveUartDev, txBuf, 20, UART_RX_TIMEOUT_MS);
  VERIFY_SUCCESS(errCode);
  errCode = UartDriver_TxAbort(driveUartDev);
  VERIFY_SUCCESS(errCode);

  k_msleep(2000);

  /* utilizing uart receive disable api */
  errCode = UartDriver_RxDisable(driveUartDev);
  VERIFY_SUCCESS(errCode);

  k_msleep(2000);

  /* utilizing uart receive enable api */
  errCode = UartDriver_RxEnable(driveUartDev, rxBuf, 20, UART_RX_TIMEOUT_MS);
  VERIFY_SUCCESS(errCode);

  k_msleep(2000);
  
  /* destroying an instance of uart driver */
  errCode = UartDriver_Destroy(&driveUartDev);
  VERIFY_SUCCESS(errCode);

  return APP_SUCCESS;
}
