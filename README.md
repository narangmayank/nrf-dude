# nrf-dude

CLI for Nordic SOC's

## nRF Dude General

- Invoke the dude use `hye dude`
- Then send some commands to execute eg. `run unit tests`
- Release the dude use `bye dude`

Invoking the dude will start a session, then after you can start sending the commands to execute and each command you sent would be follewed by a real time hardware response. Once you are done just release the dude to free up the occupied resources

See the example below,

```bash
# Run unit tests
$ nrf-dude> run unit tests
Executed! (err_code : api_error_code_comes_here)

# Unknown command
$ nrf-dude> can you execute this
Error! (Unknown Command)
```

## Supported Hardware

- [nRF9160 DK](https://www.nordicsemi.com/Products/Development-hardware/nrf9160-dk) 
- Other boards yet to be tested. Mostly it will be supported without any breaking changes. If you have tested then please raise a PR with any code changes if required and add the baord here.

## Prerequisites

* **Hardware**
    * Supported Nordic SOC
    * [USB to TTL UART Serial Convertor Module](https://www.electronicscomp.com/cp2102-usb-to-ttl-serial-converter-module?gclid=Cj0KCQjwmPSSBhCNARIsAH3cYgZYxKicZp3K4ffDAOhflVfdwYnVYaJ4WPLYOvm-uyRn7_Nrcr6eSiAaAn-jEALw_wcB)

* **Software**
    * [Segger Embedded Studio](https://www.segger.com/downloads/embedded-studio/) [Optional]
    * [nRF Connect for desktop](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-desktop)
        * Install and open the Getting started assistant
        * Follow all the steps in «Install the toolchain and SDK **v1.7.0**»
    * [nRF Command Line Tools](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Command-Line-Tools)
    * [Python](https://www.python.org/downloads/)
    * [Ruby](https://rubyinstaller.org/downloads/)

**Note**: This project is initially based on nRF Connect SDK v1.7.0. However beyond versions might be supported with minimal efforts. You can install the latest version of all the other software packages.s

## Connections

Connect the USB-TTL to any available UART port of the controller and other side to PC USB. By default UART2 is used by the **nrf-dude**. You can always change the UART port later on anytime and the same should be configured to use it too

For nRF9160 DK plese use the following pins for UART,
- Tx - P0.24
- Rx - P0.23


## Development Environment

nRF Connect SDK is used for the development of the **nrf-dude** and it utilizes Zephyr RTOS for the firmware development. You are welcome to follow Nordic's [instructions](https://www.nordicsemi.com/Products/Development-software/nrf-connect-sdk) for setting up the nRF Connect SDK

## Project Setup 

```bash
# Get the nrf-dude
$ git clone https://github.com/narangmayank/nrf-dude

# Step into the project directory
$ cd nrf-dude

# Install the python requirements
$ pip install -r requirements.txt
```

## Let's Get Started

Here I'm building the app for nRF9160 SoC. In case you are using other SoC please tune the build accordingly :)

### Option 1 : Using pre-compiled binary

```bash
# Step inside script folder
$ cd script

# Run the flasher script (i.e based on nrfjprog utility)
$ flash_hex.bat nrf91
```

### Option 2 : Generating binary (Using West)

```bash
# Setup the nrf toolchain
$ path_to_sdk/toolchain/cmd/env.cmd

# Build the binary
$ west build -b nrf9160dk_nrf9160 -d build_nrf9160dk_nrf9160_ns

# Flash the binary
$ west flash -d build_nrf9160dk_nrf9160_ns --erase
```

### Option 3 : Generating binary (Using Segger Embedded Studio)

You can also build, flash and run the nrf-dude via Segger Embedded Studio as usual :)

## nRF CLI 

```bash
# Step inside script folder
$ cd script

# Run the nrf cli script
$ python nrf_cli.py COM_PORT BAUDRATE log_session=true
```

Logging can be enabled or disabled using the log_session boolean argument. nRF CLI logs will be stored inside the [nrf-cli-logs.txt](script/nrf-cli-logs.txt) file

## Available Commands

```
# Invoke the nrf-dude
$ hye dude

# Show help message
$ help me

# Run the entire unit tests suite
$ run unit tests

# Run led module unit tests
$ run led unit tests

# Run uart module unit tests
$ run uart unit tests

# Create the LED driver instance
$ led init

# Turn ON the LED
$ led on : led_index

# Turn ON all the LED's
$ led on : all

# Turn OFF the LED
$ led off : led_index

# Turn OFF all the LED's
$ led off : all

# Toggle the LED
$ led toggle : led_index

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

## Cherry on Cake : nRF Automated CLI

Before starting, You need to setup the commands to be automated inside nrf-automated-cli-commands.txt file in line order. To just get started I've tried to put down few basic commands. You can always update the file and test in your way.

```bash
# Step inside script folder
$ cd script/Automated_CLI

# Run the nrf automated cli script
$ python nrf_automated_cli.py COM_PORT BAUDRATE log_session=true
```

Logging can be enabled or disabled using the log_session boolean argument. nRF Automated CLI logs will be stored inside the [nrf-automated-cli-logs.txt](script/Automated_CLI/nrf-automated-cli-logs.txt) file

### Contributing

Contributions are welcome!  Not only you’ll encourage the development of the nrf dude, but you’ll also learn how to best use the embedded cli and probably some C too

See [the contributing guide](CONTRIBUTING.md) for detailed instructions on how to get started with the **nrf-dude**. Please follow the [code of conduct](CODE_OF_CONDUCT.md) while contributing.

## License

This project is licensed under the Apache License, Version 2.0 (see [LICENSE](LICENSE) for details).