#!/bin/bash

# Uno R1
chip=at90usb82
# Uno R3
#chip=atmega16u2

sudo dfu-programmer ${chip} erase
sudo dfu-programmer ${chip} flash usbserial.hex
sudo dfu-programmer ${chip} reset
