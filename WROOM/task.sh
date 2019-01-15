#!/bin/sh
case "$1" in
    "app-run") 
    make app -j4&&make app-flash -j4&&make monitor -j4
    ;;
    "monitor") 
	make monitor -j4
    ;;
    "app-flash") 
	make app-flash -j4
    ;;
    "openocd") 
    taskkill -f -im openocd.exe 
#    /mingw32.exe openocd.exe -s /mingw32/share/openocd/scripts -f /mingw32/share/openocd/scripts/interface/ftdi/um232h.cfg -f /mingw32/share/openocd/scripts/board/esp-wroom-32.cfg
    openocd.exe -s /mingw32/share/openocd/scripts -f /mingw32/share/openocd/scripts/interface/ftdi/um232h.cfg -f /mingw32/share/openocd/scripts/board/esp-wroom-32.cfg
    ;;
esac
