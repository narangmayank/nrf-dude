#include "Utils.h"
#include "LedDriver/LedDriver.h"
#include <unity.h>

/* constructor for a test case (It runs before running the test case) */
void setUp() {
  LedDriver_Create();
}

/* destructor for a test case (It runs after running the test case) */
void tearDown() {
  LedDriver_Destroy();
} 

/* Initial state of leds must be off */
void test_LedsAreOffAfterCreate() {
  int expectedValue[LEDS_NUMBER];

  int actualValue[LEDS_NUMBER];
  
  for(uint32_t i=0; i<LEDS_NUMBER; i++) { 
    expectedValue[i] = true;
    actualValue[i] = LedDriver_IsOff(i);
  }

  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, LEDS_NUMBER);
}

/* Turning On a single led at a time */
void test_TurnOnOneLed() {  
  int expectedValue = APP_SUCCESS;
  int actualValue = LedDriver_TurnOn(0);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

/* Turning Off a single led at a time */
void test_TurnOffOneLed() {  
  int expectedValue = APP_SUCCESS;
  LedDriver_TurnOn(0);
  int actualValue = LedDriver_TurnOff(0);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}