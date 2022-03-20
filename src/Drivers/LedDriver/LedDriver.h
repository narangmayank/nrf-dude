#ifndef D_LedDriver_H
#define D_LedDriver_H

#include <stdint.h>
#include <stdbool.h>

#define LEDS_NUMBER    4

#define LED_1          2   
#define LED_2          3   
#define LED_3          4   
#define LED_4          5   

#define LED_START      LED_1
#define LED_STOP       LED_4

#define LEDS_ACTIVE_STATE 1

#define LEDS_LIST { LED_1 , LED_2, LED_3, LED_4  }

void LedDriver_Create();
void LedDriver_Destroy();

void LedDriver_TurnOn(uint32_t ledIdx);
void LedDriver_TurnOff(uint32_t ledIdx);

void LedDriver_TurnAllOn();
void LedDriver_TurnAllOff();

bool LedDriver_IsOn(uint32_t ledIdx);
bool LedDriver_IsOff(uint32_t ledIdx);

void LedDriver_TurnOpposite();

#endif
