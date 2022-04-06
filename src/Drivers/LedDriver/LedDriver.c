#include "Utils.h"
#include "LedDriver/LedDriver.h" 
#include <nrf9160.h>
#include <drivers/gpio.h>

/* if board is equiped with led's then only do the operations */
#if LEDS_NUMBER > 0
static const struct device * ledAddress = NULL;
static const uint8_t ledList[LEDS_NUMBER] = LEDS_LIST;
#endif

/*
 * @brief Function for creating an instance of led driver.
 *
 * @details Retrieve the device structure for a gpio driver, configuring led pins as ouptut
 *          and keeping all the led's at off state.
 *
 * @param None.
 *
 * @retval APP_SUCCESS If the instance of the led driver was successfully initialized.
 *                     Otherwise, an error code is returned.
 *
 */
int LedDriver_Create() {
  uint32_t i;
  int errCode;
  
  /* retrieve the device structure for a gpio driver and verify the same */
  ledAddress = device_get_binding("GPIO_0");
  VERIFY_PARAM_NOT_NULL(ledAddress); 
  
  /* configuring led pins as ouptut and keeping all the led's at off state */
  for (i = 0; i < LEDS_NUMBER; ++i) {
    errCode = gpio_pin_configure(ledAddress, ledList[i], LEDS_ACTIVE_STATE ? GPIO_OUTPUT_LOW : GPIO_OUTPUT_HIGH); 
    VERIFY_SUCCESS(errCode);
  }

  return APP_SUCCESS;
}

/*
 * @brief Function for destroying an instance of led driver. 
 *
 * @details Releasing the device structure for a gpio driver, configuring led pins as ouptut
 *          and keeping all the led's at off state.
 *
 * @param None
 *
 * @retval APP_SUCCESS If the instance of the led driver was successfully de-initialized.
 *                     Otherwise, an error code is returned.
 *
 */
int LedDriver_Destroy() {
  uint32_t i;
  int errCode;
  
  /* validate the led dev pointer */
  VERIFY_PARAM_NOT_NULL(ledAddress);

  /* configuring led pins as ouptut and keeping all the led's at off state */
  for (i = 0; i < LEDS_NUMBER; ++i) {
    errCode = gpio_pin_configure(ledAddress, ledList[i], LEDS_ACTIVE_STATE ? GPIO_OUTPUT_LOW : GPIO_OUTPUT_HIGH); 
    VERIFY_SUCCESS(errCode);
  }
  
  /* release the device structure for a gpio driver and verify the same */
  ledAddress = NULL;
  VERIFY_PARAM_IS_NULL(ledAddress); 

  return APP_SUCCESS;
}

/*
 * @brief Function for turning ON the respective led. 
 *
 * @param ledIdx index of led number in ledList array.
 *
 * @retval APP_SUCCESS If the led was turned ON successfully. Otherwise, an error code is returned.
 *
 */
int LedDriver_TurnOn(uint32_t ledIdx) {
  int errCode;
  
  /* validate the led dev pointer */
  VERIFY_PARAM_NOT_NULL(ledAddress);

  /* validate the led index out of bound scenario */
  ASSERT(ledIdx < LEDS_NUMBER);

  /* based on led active state , write to the led pin */
  errCode = gpio_pin_set(ledAddress, ledList[ledIdx], LEDS_ACTIVE_STATE ? 1 : 0);
  VERIFY_SUCCESS(errCode);

  return APP_SUCCESS;
}

/*
 * @brief Function for turning OFF the respective led. 
 *
 * @param ledIdx index of led number in ledList array.
 *
 * @retval APP_SUCCESS If the led was turned OFF successfully. Otherwise, an error code is returned.
 *
 */
int LedDriver_TurnOff(uint32_t ledIdx) {
  int errCode;
  
  /* validate the led dev pointer */
  VERIFY_PARAM_NOT_NULL(ledAddress);

  /* validate the led index out of bound scenario */
  ASSERT(ledIdx < LEDS_NUMBER);

  /* based on led active state , write to the led pin */
  errCode = gpio_pin_set(ledAddress, ledList[ledIdx], LEDS_ACTIVE_STATE ? 0 : 1);
  VERIFY_SUCCESS(errCode);

  return APP_SUCCESS;
}

/*
 * @brief Function for toggling the respective led. 
 *
 * @param ledIdx index of led number in ledList array.
 *
 * @retval APP_SUCCESS If the led was toggled successfully. Otherwise, an error code is returned.
 *
 */
int LedDriver_TurnOpposite(uint32_t ledIdx) {
  int errCode;
  
  /* validate the led dev pointer */
  VERIFY_PARAM_NOT_NULL(ledAddress);

  /* validate the led index out of bound scenario */
  ASSERT(ledIdx < LEDS_NUMBER);
  
  /* toggle the state of led */
  errCode = gpio_pin_toggle(ledAddress, ledList[ledIdx]);
  VERIFY_SUCCESS(errCode);

  return APP_SUCCESS;
}

/*
 * @brief Function for checking whether the respective led is ON or Not. 
 *
 * @param ledIdx index of led number in ledList array.
 *
 * @retval true If the respective led is ON. Otherwise false.
 *
 */
bool LedDriver_IsOn(uint32_t ledIdx) {
  /* validate the led dev pointer */
  VERIFY_PARAM_NOT_NULL(ledAddress);

  /* validate the led index out of bound scenario */
  ASSERT(ledIdx < LEDS_NUMBER);
  
  /* read the output port register and make a mask register based on the led number */
  bool pinStatus = false;
  uint32_t OUTPUT_PORT = NRF_P0_NS->OUT;
  uint32_t OUTPUT_MASK = 1U << ledList[ledIdx];

  /* compare (AND Operation) and check for that particular pin */
  pinStatus = OUTPUT_PORT & OUTPUT_MASK;
  
  /* based on led active state , return true or false */
  return (pinStatus == (LEDS_ACTIVE_STATE ? true : false));
}

/*
 * @brief Function for checking whether the respective led is OFF or Not. 
 *
 * @param ledIdx index of led number in ledList array.
 *
 * @retval true If the respective led is OFF. Otherwise false.
 *
 */
bool LedDriver_IsOff(uint32_t ledIdx) {
  /* validate the led dev pointer */
  VERIFY_PARAM_NOT_NULL(ledAddress);

  /* validate the led index out of bound scenario */
  ASSERT(ledIdx < LEDS_NUMBER);
  
  /* just return the opposite of LedDriver_IsOn() */
  return !LedDriver_IsOn(ledIdx);
}

/*
 * @brief Function for turning ON all the available led's. 
 *
 * @param None.
 *
 * @retval APP_SUCCESS If all led's was turned ON successfully. Otherwise, an error code is returned.
 *
 */
int LedDriver_TurnAllOn() {
  uint32_t i;
  int errCode;
  
  /* validate the led dev pointer */
  VERIFY_PARAM_NOT_NULL(ledAddress);

  /* turn ON all the led's which are there in ledList array */
  for (i = 0; i < LEDS_NUMBER; ++i) {
      errCode = LedDriver_TurnOn(i);
      VERIFY_SUCCESS(errCode);
  }

  return APP_SUCCESS;
}

/*
 * @brief Function for turning OFF all the available led's. 
 *
 * @param None.
 *
 * @retval APP_SUCCESS If all led's was turned OFF successfully. Otherwise, an error code is returned.
 *
 */
int LedDriver_TurnAllOff() {
  uint32_t i;
  int errCode;
  
  /* validate the led dev pointer */
  VERIFY_PARAM_NOT_NULL(ledAddress);

  /* turn ON all the led's which are there in ledList array */
  for (i = 0; i < LEDS_NUMBER; ++i) {
      errCode = LedDriver_TurnOff(i);
      VERIFY_SUCCESS(errCode);
  }

  return APP_SUCCESS;
}

/*
 * @brief Function for toggling all the available led's. 
 *
 * @param None.
 *
 * @retval APP_SUCCESS If all led's was toggled successfully. Otherwise, an error code is returned.
 *
 */
int LedDriver_TurnAllOpposite() {
  uint32_t i;
  int errCode;
  
  /* validate the led dev pointer */
  VERIFY_PARAM_NOT_NULL(ledAddress);

  /* toggle all the led's which are there in ledList array */
  for (i = 0; i < LEDS_NUMBER; ++i) {
      errCode = LedDriver_TurnOpposite(i);
      VERIFY_SUCCESS(errCode);
  }

  return APP_SUCCESS;
}

/*
 * @brief Function for checking whether all the led's are ON or Not. 
 *
 * @param None.
 *
 * @retval true If all the led's are ON. Otherwise false.
 *
 */
bool LedDriver_IsAllOn() {
  uint32_t i;
  bool ledStatus;
  
  /* validate the led dev pointer */
  VERIFY_PARAM_NOT_NULL(ledAddress);

  /* check whether all the led's are ON or not */
  for (i = 0; i < LEDS_NUMBER; ++i) {
      ledStatus = LedDriver_IsOn(i);

      /* if any led found to be off, return from there and give false */
      if(ledStatus == false) {
        return ledStatus;
      }
  }
  
  return ledStatus;
}

/*
 * @brief Function for checking whether all the led's are OFF or Not. 
 *
 * @param None.
 *
 * @retval true If all the led's are OFF. Otherwise false.
 *
 */
bool LedDriver_IsAllOff() {
  /* validate the led dev pointer */
  VERIFY_PARAM_NOT_NULL(ledAddress);
  
  /* just return the opposite of LedDriver_IsOn() */
  return !LedDriver_IsAllOn();
}