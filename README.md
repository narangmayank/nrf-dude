# Run Time CLI for Embedded Systems in Bhailang Style


## nrf-bhai command's

* hi bhai
    * Call the nrf-bhai
* unit tests run kar bhai
    * Run the Unit tests
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
* bye bhai
    * Release the nrf-bhai

## Steps to build this demo

```bash
git clone https://github.com/Mayank-124/RunTimeCli.git
cd RunTimeCli
batch\flash_hex.bat
```

## RunTime CLI
```bash
cd script\RunTimeCli
python RunTimeCli.py  COM_PORT BAUDRATE
eg. python RunTimeCli.py COM6 115200

Call the nrf bhai with "hi bhai" command

nrf-bhai>your command goes here
bhai response comes here

Release the nrf bhai with "bye bhai" command

:: Run Time Cli Session Logs will be stored inside cliLogs.txt file under RunTimeCli folder.
```

## Automated CLI
```bash
cd script\AutomatedCli
python AutomatedCli.py COM_PORT BAUDRATE
eg. python AutomatedCli.py COM6 115200

:: You can setup your commands to automate inside cliCommands.txt file line by line 

:: Automated Cli Session Logs will be stored inside cliLogs.txt file under AutomatedCli folder
```

### Contribute
Wanna Contribute? Give the [contribution guide](https://github.com/Mayank-124/RunTimeCli/blob/main/CONTRIBUTING.md) a read.