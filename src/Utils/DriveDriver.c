#include "Utils.h"
#include "DriveDriver.h" 
#include "LedDriver/LedDriver.h" 
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
