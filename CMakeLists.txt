cmake_minimum_required(VERSION 3.13.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(RunTimeCli)

# source files
target_sources(app PRIVATE src/main.c)
