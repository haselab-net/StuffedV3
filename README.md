# Stuffed toy robot version 3 (Starts from 2017) 

This repository contains Motor driver boards'schematics / PCB layouts, their firmwares and PC software.

## Folder structure
- __PIC__ Firmware for pic.
- __WROOM__ Firmware for WROOM.
- __PCRobokey__ Windows software to control the robot.

# Architecture
WROOM: The main board. One robot has one board.
PIC: Motor driver extension board. Upto eight PIC boards share one UART to communicate with the main WROOM board.

# PIC
## Compiler
MPLABXIDE and XC32 compiler are needed. Install latest of both. Free vesion is enough.
- http://www.microchip.com/mplab/mplab-x-ide see download tab
- http://www.microchip.com/mplab/compilers see download tab

## Setting Macros in the source code.
There are some kinds of boards using the same firmware. So please define appropriate macro for your board.
 See __PIC/boardType.h__ and choose appropriate macro.
In addition, each board sharing the same UART should have different IDs. The ID must be 0 to 7.

# WROOM
 Haoyan Li made a development environment and tutorial.
 See https://github.com/VirgiliaBeatrice/esp32-devenv-vscode and install it.

# PCRobokey
Visual Studio 2015 (14) is used to build. Newer will also work.
