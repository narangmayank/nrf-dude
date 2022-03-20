/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "LedDriver/LedDriver.h"

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>

void ledStatusCheck() {
  printk("**************************************\n");

  printk("%s\n",LedDriver_IsOn(0) ? "true" : "false");
  printk("%s\n",LedDriver_IsOn(1) ? "true" : "false");
  printk("%s\n",LedDriver_IsOn(2) ? "true" : "false");
  printk("%s\n",LedDriver_IsOn(3) ? "true" : "false");
  
  printk("\n");

  printk("%s\n",LedDriver_IsOff(0) ? "true" : "false");
  printk("%s\n",LedDriver_IsOff(1) ? "true" : "false");
  printk("%s\n",LedDriver_IsOff(2) ? "true" : "false");
  printk("%s\n",LedDriver_IsOff(3) ? "true" : "false");

  printk("**************************************\n");
}
void main(void) {
  LedDriver_Create();
  
  ledStatusCheck();
  LedDriver_TurnOn(0);
  ledStatusCheck();
  LedDriver_TurnOn(1);
  ledStatusCheck(); 
  LedDriver_TurnOn(2);
  ledStatusCheck();
  LedDriver_TurnOn(3);
  ledStatusCheck();

  LedDriver_Destroy();
}
