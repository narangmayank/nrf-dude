/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "DriveDriver.h"
#include "LedDriver/LedDriver.h"
#include "UartDriver/UartDriver.h"
#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <sys/printk.h>

void main(void) {
  printk("err_code : %d",driveLed());
}
