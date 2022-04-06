#ifndef D_LedDriver_H
#define D_LedDriver_H

#include <stdint.h>
#include <stdbool.h>

/* number of leds on the board */
#define LEDS_NUMBER    4

/* defines the hardware configuartion of the led */
#define LEDS_ACTIVE_STATE 1

/* led pin numbers */
#define LED_1          2   
#define LED_2          3   
#define LED_3          4   
#define LED_4          5   

#define LED_START      LED_1      // first led
#define LED_STOP       LED_4      // last led


/* array to hold the pin numbers of each led , we will gonna access these pin
 * numbers by their respective index (ledIdx) 
 */
#define LEDS_LIST { LED_1 , LED_2, LED_3, LED_4 }


/* function prototypes start */

int LedDriver_Create();
int LedDriver_Destroy();

int LedDriver_TurnOn(uint32_t ledIdx);
int LedDriver_TurnOff(uint32_t ledIdx);
int LedDriver_TurnOpposite(uint32_t ledIdx);

bool LedDriver_IsOn(uint32_t ledIdx);
bool LedDriver_IsOff(uint32_t ledIdx);

int LedDriver_TurnAllOn();
int LedDriver_TurnAllOff();
int LedDriver_TurnAllOpposite();

bool LedDriver_IsAllOn();
bool LedDriver_IsAllOff();

/* function prototypes end  */

#endif /* D_LedDriver_H */
