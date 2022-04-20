cmake_minimum_required(VERSION 3.13.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(RunTimeCli)

# no need of unity_memroy src as of now
add_definitions(-DUNITY_FIXTURE_NO_EXTRAS)
 
# add unity_fixture module to the project (i.e not included inside unity CMakeLists)
zephyr_include_directories(${ZEPHYR_BASE}/../test/cmock/vendor/unity/extras/fixture/src)
target_sources(app PRIVATE ${ZEPHYR_BASE}/../test/cmock/vendor/unity/extras/fixture/src/unity_fixture.c)

# header files
zephyr_include_directories(src/App)
zephyr_include_directories(src/Drivers)
zephyr_include_directories(src/Utils)
zephyr_include_directories(test/TestRunner)

# source files
target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/App/Cli/Cli.c)
target_sources(app PRIVATE src/App/Cli/CmdHandler.c)
target_sources(app PRIVATE src/App/UartThread/UartThread.c)
target_sources(app PRIVATE src/Drivers/LedDriver/LedDriver.c)
target_sources(app PRIVATE src/Drivers/UartDriver/UartDriver.c)
target_sources(app PRIVATE src/Utils/DriveDriver.c)

# test files
target_sources(app PRIVATE test/LedTest.c)
target_sources(app PRIVATE test/TestRunner/TestRunner.c)