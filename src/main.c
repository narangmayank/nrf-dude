/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>

void main(void) {

  while(1) { 
    printk("Hi, I am an instance of Run time Cli !!\n");
    k_msleep(1000);
  }
}
