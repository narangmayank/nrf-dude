#include "TestRunner.h" 
#include <unity_fixture.h>

/* run all the test groups */
void RunAllTestGroups(void) {
  RUN_TEST_GROUP(LedTestGroup);
} 

/* run led test group */
void RunLedTestGroup(void) {
  RUN_TEST_GROUP(LedTestGroup);
} 
