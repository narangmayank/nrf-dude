cmake_minimum_required(VERSION 3.13.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(RunTimeCli)

# header files
zephyr_include_directories(src/Drivers)
zephyr_include_directories(src/Utils)

# source files
target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/Utils/DriveDriver.c)
target_sources(app PRIVATE src/Drivers/LedDriver/LedDriver.c)
target_sources(app PRIVATE src/Drivers/UartDriver/UartDriver.c)

# test files
target_sources(app PRIVATE test/LedTest.c)

# runner test file generation
test_runner_generate(test/LedTest.c)