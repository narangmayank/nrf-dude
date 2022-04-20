# Run Time CLI for Embedded Systems in Bhailang Style


## nrf-bhai command's

* hi bhai
    * Call the nrf-bhai
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
    * [nRF Connect for desktop](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-desktop) v3.3.0 (or newer)
        * Install and open the Getting started assistant
        * Follow all the steps in «Install the toolchain»
    * [nRF Command Line Tools](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Command-Line-Tools) v10.5.0 (or newer)

## Steps to build this demo

```bash
git clone https://github.com/Mayank-124/RunTimeCli.git
cd RunTimeCli
batch\flash_hex.bat
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

:: Run Time Cli Session Logs will be stored inside cliLogs.txt file under RunTimeCli folder.
```

## Automated CLI
```bash
cd script\AutomatedCli
python AutomatedCli.py COM_PORT BAUDRATE LOG_OPTION
eg. python AutomatedCli.py COM6 115200 LogSession

:: You can setup your commands to automate inside cliCommands.txt file line by line 

:: Automated Cli Session Logs will be stored inside cliLogs.txt file under AutomatedCli folder
```

### Contribute
Wanna Contribute? Give the [contribution guide](https://github.com/Mayank-124/RunTimeCli/blob/main/CONTRIBUTING.md) a read.