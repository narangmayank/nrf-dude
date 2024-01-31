#include "Utils.h"
#include "UartDriver/UartDriver.h"
#include <errno.h>
#include <unity.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <unity_fixture.h>

uint8_t Test_uartDevRxBuf[20] = "";
const struct device * Test_uartDev = NULL;

/* Test Group for uart module */
TEST_GROUP(UartTestGroup); 

/* constructor for a test case for UartTestGroup (It runs before running the test case) */
TEST_SETUP(UartTestGroup) {
  UartDriver_Create(&Test_uartDev, UART_PORT_0, UART_BAUDRATE_115200);
}

/* destructor for a test case for UartTestGroup (It runs after running the test case) */
TEST_TEAR_DOWN(UartTestGroup) {
  UartDriver_Destroy(&Test_uartDev);
}

/* transmit data from uart */
TEST(UartTestGroup, UartTxData) {
  uint8_t data[] = " ***dummy data from UartTxData test case*** ";
  
  int expectedValue = APP_SUCCESS;
  int actualValue = UartDriver_TxData(Test_uartDev, data, strlen(data), UART_RX_TIMEOUT_MS);
  k_msleep(100);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
} 

/* abort current uart transmission */
TEST(UartTestGroup, UartTxAbort) {
  uint8_t data[] = " ***dummy data from UartTxAbort test case*** ";
  UartDriver_TxData(Test_uartDev, data, strlen(data), UART_RX_TIMEOUT_MS);

  int expectedValue = APP_SUCCESS;
  int actualValue = UartDriver_TxAbort(Test_uartDev);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
} 

/* abort currenr uart transmission does no harm */
TEST(UartTestGroup, UartTxAbortDoesNoHarm) {
  int expectedValue = -EFAULT;
  int actualValue = UartDriver_TxAbort(Test_uartDev);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
} 

/* enable uart reception */
TEST(UartTestGroup, UartRxEnable) {
  int expectedValue = APP_SUCCESS;
  int actualValue = UartDriver_RxEnable(Test_uartDev, Test_uartDevRxBuf, 20, UART_RX_TIMEOUT_MS);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
} 

/* disable uart reception */
TEST(UartTestGroup, UartRxDisable) {
  int expectedValue = APP_SUCCESS;
  int actualValue = UartDriver_RxDisable(Test_uartDev);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
} 

/*********************************** Runner of UartTestGroup starts ***********************************/


TEST_GROUP_RUNNER(UartTestGroup)
{
  // Uart tx checks
  RUN_TEST_CASE(UartTestGroup, UartTxData);
  RUN_TEST_CASE(UartTestGroup, UartTxAbort);
  RUN_TEST_CASE(UartTestGroup, UartTxAbortDoesNoHarm);

  // Uart rx checks
  RUN_TEST_CASE(UartTestGroup, UartRxEnable);
  RUN_TEST_CASE(UartTestGroup, UartRxDisable);
}
 

/***********************************  Runner of UartTestGroup ends  ***********************************/
