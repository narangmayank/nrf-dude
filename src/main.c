/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "LedDriver/LedDriver.h"

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>

void main(void) {
  int err_code;

  err_code = LedDriver_Create();
  printk("err_code : %d\n", err_code);
  
  err_code = LedDriver_TurnOn(-1);
  printk("err_code : %d\n", err_code);

  err_code = LedDriver_TurnOn(0);
  printk("err_code : %d\n", err_code);
  
  err_code = LedDriver_TurnOn(4);
  printk("err_code : %d\n", err_code);

  err_code = LedDriver_Destroy();
  printk("err_code : %d\n", err_code); 
}
