# Run Time CLI for Embedded Systems in Bhailang Style

## nrf-bhai Cli General

```bash
nrf-bhai>your command goes here
bhai response comes here

&&

nrf-bhai> "ye" kar bhai
bhai response idhar aaega

:: Command syntax
task : args 
eg. led on kar bhai : 2

here args purely depends upon the task you are going to perform, for better understanding please refer to nrf-bhai commands

:: Response syntax

If command found then,
Shandaar Bhai (err_code : api_error_code_comes_here)   <--- Green Color --->

If command not found then,
Arre Bhai Bhai Bhai !!! (Unknown Command)              <---  Red Color  --->
```

## nrf-bhai command's

* hi bhai
    * Call the nrf-bhai
* help kar bhai
    * Show available commands along with syntax
* unit tests run kar bhai
    * Run the Unit tests
* led unit tests run kar bhai
    * Run the led module unit tests
* uart unit tests run kar bhai
    * Run the uart module unit tests
* led instance create kar bhai
    * Init the led module
* led on kar bhai : led_index
    * Turn ON the led with index led_index where led_index can be {0, 1, 2, 3, all}
* led off kar bhai : led_index
    * Turn OFF the led with index led_index where led_index can be {0, 1, 2, 3, all}
* led toggle kar bhai : led_index
    * Toggle the led with index led_index where led_index can be {0, 1, 2, 3, all}
* led instance destroy kar bhai
    * De-Init the led module
* uart instance create kar bhai
    * Init the uart module
* uart tx kar bhai : tx_data
    * Transmit data from uart with data as tx_data
* uart tx abort kar bhai
    * Abort the ongoing uart transmission if any
* uart rx enable kar bhai
    * Enable the uart reception
* uart rx disable kar bhai
    * Disable the uart reception
* uart instance destroy kar bhai
    * De-Init the uart module
* bye bhai
    * Release the nrf-bhai

## Development Environment
Nordic Semiconductor have chosen Zephyr RTOS for firmware development on the nRF9160. You are welcome to follow Nordic's [instructions](https://www.nordicsemi.com/Products/Development-software/nrf-connect-sdk) for setting up the nRF Connect SDK. Currently it's based on [nRF Connect SDK](https://www.nordicsemi.com/Products/Development-software/nrf-connect-sdk) **v1.7.0**.

## Prerequisites

* **Hardware**
    * The [nRF9160 DK](https://www.nordicsemi.com/Products/Development-hardware/nrf9160-dk)  
    * Micro-USB cable
    * [USB to TTL UART Serial Convertor Module](https://www.electronicscomp.com/cp2102-usb-to-ttl-serial-converter-module?gclid=Cj0KCQjwmPSSBhCNARIsAH3cYgZYxKicZp3K4ffDAOhflVfdwYnVYaJ4WPLYOvm-uyRn7_Nrcr6eSiAaAn-jEALw_wcB)

* **Software**
    * [Segger Embedded Studio](https://www.segger.com/downloads/embedded-studio/) v5.0(or newer)
    * [nRF Connect for desktop](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-desktop) v3.3.0 (or newer)
        * Install and open the Getting started assistant
        * Follow all the steps in «Install the toolchain»
    * [nRF Command Line Tools](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Command-Line-Tools) v10.5.0 (or newer)
    * pip install pyserial colored (if not have)

## Steps to build this demo

Using pre-coimpiled binary
```bash
git clone https://github.com/Mayank-124/RunTimeCli.git
cd RunTimeCli
batch\flash_hex.bat
```

Generating binary on your end using commands
```bash
git clone https://github.com/Mayank-124/RunTimeCli.git
cd RunTimeCli
rmdir /s /q build_nrf9160dk_nrf9160_ns
path_to_sdk\toolchain\cmd\env.cmd
west build -b nrf9160dk_nrf9160 -d build_nrf9160dk_nrf9160_ns
west flash -d build_nrf9160dk_nrf9160_ns --erase
```

Generating binary on your end using IDE
```bash
git clone https://github.com/Mayank-124/RunTimeCli.git
cd RunTimeCli
rmdir /s /q build_nrf9160dk_nrf9160_ns
path_to_sdk\toolchain\"SEGGER Embedded Studio.cmd"

IDE will pop up now , just follow the below instruction in IDE 
File ----> Open nRF Connect SDK Project
Select the RunTimeCli Project
Select the board as nrf9160dk_nrf9160_ns
Build and Run the Solution
```

## RunTime CLI
```bash
cd script\RunTimeCli
python RunTimeCli.py  COM_PORT BAUDRATE LOG_OPTION
eg. python RunTimeCli.py COM6 115200 LogSession

Call the nrf bhai with "hi bhai" command

nrf-bhai>your command goes here
bhai response comes here

Release the nrf bhai with "bye bhai" command

:: If you want to enbale logging just give the extra argumnet LogSession while running the python script otherwise you can go with only COM Port and Baudrate

:: Run Time Cli Session Logs will be stored inside cliLogs.txt file under RunTimeCli folder if logging is enabled
```

## Automated CLI
```bash
cd script\AutomatedCli
python AutomatedCli.py COM_PORT BAUDRATE LOG_OPTION
eg. python AutomatedCli.py COM6 115200 LogSession

:: If you want to enbale logging just give the extra argumnet LogSession while running the python script otherwise you can go with only COM Port and Baudrate

:: You can setup your commands to automate inside cliCommands.txt file line by line 

:: Automated Cli Session Logs will be stored inside cliLogs.txt file under AutomatedCli folder if logging is enabled
```

### Contribute
Wanna Contribute? Give the [contribution guide](https://github.com/Mayank-124/RunTimeCli/blob/main/CONTRIBUTING.md) a read.