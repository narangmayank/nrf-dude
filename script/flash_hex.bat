@echo off

nrfjprog -f nrf91 --program ..\hex\merged.hex --sectorerase
nrfjprog --reset