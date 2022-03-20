/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "LedDriver/LedDriver.h"
#include "UartDriver/UartDriver.h"

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>

const struct device * uartDev = NULL;
uint8_t txBuf[30] = "Hi, I am uart 0 port buffer\n\r";

void main(void) {
  int err_code;

  err_code = UartDriver_Create(&uartDev, UART_PORT_0, UART_BAUDRATE_115200);
  printk("err_code : %d\n", err_code);
    
  k_msleep(5000);

  err_code = UartDriver_TxData(uartDev, txBuf, 30, 50);
  printk("err_code : %d\n", err_code);

  k_msleep(5000);

  err_code = UartDriver_Destroy(&uartDev);
  printk("err_code : %d\n", err_code);
}
