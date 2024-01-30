# nrf-dude

CLI for Nordic SOC's

## nRF Dude General

- Invoke the dude use `hey dude`
- Then send some commands to execute eg. `run unit tests`
- Release the dude use `bye dude`

Once you invoked the dude a dude session will start, then after you can start sending the commands to execute and the response would be based on the command you sent. Once you are done just release the dude to free up the occupied resources

See the example below,

```bash
# Run unit tests
nrf-dude> run unit tests
Executed! (err_code : api_error_code_comes_here)

# Unknown command
nrf-dude> can you execute this
Error! (Unknown Command)
```

## Prerequisites

* **Hardware**
    * Any Nordic SOC
    * [USB to TTL UART Serial Convertor Module](https://www.electronicscomp.com/cp2102-usb-to-ttl-serial-converter-module?gclid=Cj0KCQjwmPSSBhCNARIsAH3cYgZYxKicZp3K4ffDAOhflVfdwYnVYaJ4WPLYOvm-uyRn7_Nrcr6eSiAaAn-jEALw_wcB)

* **Software**
    * [Segger Embedded Studio](https://www.segger.com/downloads/embedded-studio/) v5.0(or newer)
    * [nRF Connect for desktop](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-desktop) v3.3.0 (or newer)
        * Install and open the Getting started assistant
        * Follow all the steps in «Install the toolchain»
    * [nRF Command Line Tools](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Command-Line-Tools) v10.5.0 (or newer)
    * pip install pyserial colored (if not have)

## Connections

Connect the USB-TTL to any availabke UART port of the controller and other side to PC USB. By default UART2 is used by the ***nrf-dude*. You can always change the UART port later on anytime and the same should be configured to use it too

## Development Environment

nRF Connect SDK is used for the development of the **nrf-dude** and it utilizes Zephyr RTOS for the firmware development. You are welcome to follow Nordic's [instructions](https://www.nordicsemi.com/Products/Development-software/nrf-connect-sdk) for setting up the nRF Connect SDK

## Project Setup 

```bash
# Get the nrf-dude
$ git clone https://github.com/narangmayank/nrf-dude

# Step into the project directory
$ cd nrf-dude
```

## Getting Started

### Option 1 : Using pre-compiled binary

```bash
# Run the flasher script
$  batch\flash_hex.bat
```

### Option 2 : Generating binary (Using West)

```bash
# Setup the nrf toolchain
$ path_to_sdk\toolchain\cmd\env.cmd

# Build the binary
$ west build -b nrf9160dk_nrf9160 -d build_nrf9160dk_nrf9160_ns

# Flash the binary
$ west flash -d build_nrf9160dk_nrf9160_ns --erase
```

### Option 3 : Generating binary (Using Segger)

You can also build, flash and run the nrf-dude via Segger Embedded Studio as usual :)

## Running CLI 

```bash
# Step inside script folder
$ cd script

# Run the nrf cli script
$ python nrf_cli.py COM_PORT BAUDRATE log_session=true
```

Logging can be enabled or disabled using the log_session boolean argument. Running CLI logs will be stored inside the nrf-cli-logs.txt file

## Available Commands

```
# Invoke the nrf-dude
$ hey dude

# Show help message
$ help me

# Run the unit tests suite
$ run unit tests

# Create the LED driver instance
$ led init

# Turn ON the LED
$ led on : index

# Turn ON all the LED's
$ led on : all

# Turn OFF the LED
$ led off : index

# Turn OFF all the LED's
$ led off : all

# Toggle the LED
$ led toggle : index

# Toggle all the LED's
$ led toggle : all

# Destroy the LED driver instance
$ led deinit

# Create the UART driver instance
$ uart init

# Transmit data from UART
$ uart tx : data_to_send

# Abort UART Transmit
$ uart tx abort

# Enable UART Reception
$ uart rx enable

# Disable UART Reception
$ uart rx disable

# Destroy the UART driver instance
$ uart deinit

# Release the nrf-dude
$ bye dude

```

## Bonus : Automated CLI

Before starting, You can setup the commands to be automated inside nrf-automated-cli-commands.txt file in line order

```bash
# Step inside script folder
$ cd script

# Run the nrf automated cli script
$ python nrf_automated_cli.py COM_PORT BAUDRATE log_session=true
```

Logging can be enabled or disabled using the log_session boolean argument. Automated CLI logs will be stored inside the nrf-automated-cli-logs.txt file

### Contribute

Contributions are welcome!  Not only you’ll encourage the development of the nrf dude, but you’ll also learn how to best use the embedded cli and probably some C too

Please read the [contributing guide](https://github.com/Mayank-124/RunTimeCli/blob/main/CONTRIBUTING.md)
before contributing to help this project stay welcoming.