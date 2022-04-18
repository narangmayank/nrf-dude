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

/* Initial state of leds must be OFF */
void test_LedsAreOffAfterCreate() {
  int expectedValue[LEDS_NUMBER];

  int actualValue[LEDS_NUMBER];
  
  for(uint32_t i=0; i<LEDS_NUMBER; i++) { 
    expectedValue[i] = true;
    actualValue[i] = LedDriver_IsOff(i);
  }

  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, LEDS_NUMBER);
}

/* Turning ON a single led at a time */
void test_TurnOnOneLed() {  
  int expectedValue = APP_SUCCESS;
  int actualValue = LedDriver_TurnOn(0);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

/* Turning OFF a single led at a time */
void test_TurnOffOneLed() { 
  LedDriver_TurnOn(0);

  int expectedValue = APP_SUCCESS;
  int actualValue = LedDriver_TurnOff(0);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

/* Toggle a single led at a time */
void test_TogglefOneLed() { 
  int expectedValue = APP_SUCCESS;
  int actualValue = LedDriver_TurnOpposite(0);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

/* Is single led ON at a time */
void test_IsOneLedOn() { 
  LedDriver_TurnOn(0);

  int expectedValue = true;
  int actualValue = LedDriver_IsOn(0);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

/* Is single led OFF at a time */
void test_IsOneLedOff() { 
  int expectedValue = true;
  int actualValue = LedDriver_IsOff(0);
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

/* Turning ON multiple led's at a time */
void test_TurnOnMultipleLed() {  
  int expectedValue[2] = {APP_SUCCESS, APP_SUCCESS};

  int actualValue[2];
  actualValue[0] = LedDriver_TurnOn(1);
  actualValue[1] = LedDriver_TurnOn(3);

  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, 2);
}

/* Turning OFF multiple led's at a time */
void test_TurnOffMultipleLed() {  
  LedDriver_TurnOn(1);
  LedDriver_TurnOn(3);

  int expectedValue[2] = {APP_SUCCESS, APP_SUCCESS};

  int actualValue[2];
  actualValue[0] = LedDriver_TurnOff(1);
  actualValue[1] = LedDriver_TurnOff(3);

  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, 2);
}

/* Toggle multiple led's at a time */
void test_ToggleMultipleLed() {  
  int expectedValue[2] = {APP_SUCCESS, APP_SUCCESS};

  int actualValue[2];
  actualValue[0] = LedDriver_TurnOpposite(1);
  actualValue[1] = LedDriver_TurnOpposite(3);

  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, 2);
}

/* Is multiple led's ON at a time */
void test_IsMultipleLedOn() {  
  LedDriver_TurnOn(1);
  LedDriver_TurnOn(3);

  int expectedValue[2] = {true, true};

  int actualValue[2];
  actualValue[0] = LedDriver_IsOn(1);
  actualValue[1] = LedDriver_IsOn(3);

  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, 2);
}

/* Is multiple led's OFF at a time */
void test_IsMultipleLedOff() {  
  int expectedValue[2] = {true, true};

  int actualValue[2];
  actualValue[0] = LedDriver_IsOff(1);
  actualValue[1] = LedDriver_IsOff(3);

  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, 2);
}

/* Turning On all led's at a time */
void test_TurnOnAllLed() {  
  int expectedValue = APP_SUCCESS;
  int actualValue = LedDriver_TurnAllOn();
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

/* Turning Off all led's at a time */
void test_TurnOffAllLed() {  
  LedDriver_TurnAllOn();

  int expectedValue = APP_SUCCESS;
  int actualValue = LedDriver_TurnAllOff();
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

/* Toggle all led's at a time */
void test_ToggleAllLed() {  
  int expectedValue = APP_SUCCESS;
  int actualValue = LedDriver_TurnAllOpposite();
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

/* Is all led's ON at a time */
void test_IsAllLedOn() {
  LedDriver_TurnAllOn();

  int expectedValue = true;
  int actualValue = LedDriver_IsAllOn();
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

/* Is all led's OFF at a time */
void test_IsAllLedOff() {  
  int expectedValue = true;
  int actualValue = LedDriver_IsAllOff();
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

/* Out of bounds Turn ON does no harm */
void test_OutOfBoundsTurnOnDoesNoHarm() {  
  int expectedValue[2] = { APP_ERROR_ASSERTION_FAILED, APP_ERROR_ASSERTION_FAILED };

  int actualValue[2];
  actualValue[0] = LedDriver_TurnOn(-1);
  actualValue[1] = LedDriver_TurnOn(LEDS_NUMBER);

  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, 2);
}

/* Out of bounds Turn OFF does no harm */
void test_OutOfBoundsTurnOffDoesNoHarm() {  
  int expectedValue[2] = { APP_ERROR_ASSERTION_FAILED, APP_ERROR_ASSERTION_FAILED };

  int actualValue[2];
  actualValue[0] = LedDriver_TurnOff(-1);
  actualValue[1] = LedDriver_TurnOff(LEDS_NUMBER);

  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, 2);
}

/* Out of bounds Toggle does no harm */
void test_OutOfBoundsToggleDoesNoHarm() {  
  int expectedValue[2] = { APP_ERROR_ASSERTION_FAILED, APP_ERROR_ASSERTION_FAILED };

  int actualValue[2];
  actualValue[0] = LedDriver_TurnOpposite(-1);
  actualValue[1] = LedDriver_TurnOpposite(LEDS_NUMBER);

  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, 2);
}

/* Out of bounds IsOn does no harm */
void test_OutOfBoundsIsOnDoesNoHarm() {  
  int expectedValue[2] = { APP_ERROR_ASSERTION_FAILED, APP_ERROR_ASSERTION_FAILED };

  int actualValue[2];
  actualValue[0] = LedDriver_IsOn(-1);
  actualValue[1] = LedDriver_IsOn(LEDS_NUMBER);
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, 2);
}

/* Out of bounds IsOff does no harm */
void test_OutOfBoundsIsOffDoesNoHarm() {  
  int expectedValue[2] = { APP_ERROR_ASSERTION_FAILED, APP_ERROR_ASSERTION_FAILED  };

  int actualValue[2];
  actualValue[0] = LedDriver_IsOff(-1);
  actualValue[1] = LedDriver_IsOff(LEDS_NUMBER);

  TEST_ASSERT_EQUAL_INT_ARRAY(expectedValue, actualValue, 2);
}




