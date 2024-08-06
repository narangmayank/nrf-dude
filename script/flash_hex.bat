@echo off

:: Define the list of nRF targets
set "nRFTargets=nrf91 nrf51 nrf52 nrf53 unknown"

:: Check if the user provided an argument
if "%1"=="" (
    echo No target provided. Please run the script with the target as an argument.
    echo Usage: %0 target_family
    exit /b 1
)

:: Set the target
set target=%1

:: Check if the target is in the nRF targets
set targetFound=0
for %%n in (%nRFTargets%) do (
    if /i "%%n"=="%target%" (
        set targetFound=1
        goto :targetCheckDone
    )
)

:targetCheckDone
if %targetFound%==0 (
    echo Error: %target% is not in the nRF targets.
    exit /b 1
)

:: Download Cmd
nrfjprog -f %target% --program ..\hex\merged.hex --sectorerase

:: Reset Cmd
nrfjprog --reset