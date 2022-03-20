#include "LedDriver/LedDriver.h" 
#include <nrf9160.h>
#include <sys/printk.h>
#include <drivers/gpio.h>

#if LEDS_NUMBER > 0
static const struct device * ledAddress = NULL;
static const uint8_t ledList[LEDS_NUMBER] = LEDS_LIST;
#endif

void LedDriver_Create() {
  ledAddress = device_get_binding("GPIO_0");

  uint32_t i;
  for (i = 0; i < LEDS_NUMBER; ++i) {
    gpio_pin_configure(ledAddress, ledList[i], LEDS_ACTIVE_STATE ? GPIO_OUTPUT_LOW : GPIO_OUTPUT_HIGH); 
  }
}

void LedDriver_Destroy() {
  uint32_t i;
  for (i = 0; i < LEDS_NUMBER; ++i) {
    gpio_pin_configure(ledAddress, ledList[i], LEDS_ACTIVE_STATE ? GPIO_OUTPUT_LOW : GPIO_OUTPUT_HIGH); 
  }

  ledAddress = NULL;
}

void LedDriver_TurnOn(uint32_t ledIdx) {
  gpio_pin_set(ledAddress, ledList[ledIdx], LEDS_ACTIVE_STATE ? 1 : 0);
}

void LedDriver_TurnOff(uint32_t ledIdx) {
  gpio_pin_set(ledAddress, ledList[ledIdx], LEDS_ACTIVE_STATE ? 0 : 1);
}

void LedDriver_TurnAllOn() {
  uint32_t i;
  for (i = 0; i < LEDS_NUMBER; ++i) {
      LedDriver_TurnOn(i);
  }
}

void LedDriver_TurnAllOff() {
  uint32_t i;
  for (i = 0; i < LEDS_NUMBER; ++i) {
      LedDriver_TurnOff(i);
  }
}

bool LedDriver_IsOn(uint32_t ledIdx) {
  bool pinStatus = false;
  uint32_t OUTPUT_PORT = NRF_P0_NS->OUT;
  uint32_t OUTPUT_MASK = 1U << ledList[ledIdx];

  pinStatus = OUTPUT_PORT & OUTPUT_MASK;

  return (pinStatus == (LEDS_ACTIVE_STATE ? true : false));
}

bool LedDriver_IsOff(uint32_t ledIdx) {
  return !LedDriver_IsOn(ledIdx);
}

void LedDriver_TurnOpposite(uint32_t ledIdx) {
  gpio_pin_toggle(ledAddress, ledList[ledIdx]);
}
