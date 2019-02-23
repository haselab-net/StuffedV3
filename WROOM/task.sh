#!/bin/sh
case "$1" in
    "app-run") 
    make app -j8&&make app-flash -j8&&make monitor -j8
    ;;
    "monitor") 
	make monitor -j8
    ;;
    "app-flash") 
	make app-flash -j8
    ;;
    "openocd") 
    taskkill -f -im openocd.exe 
#    /mingw32.exe openocd.exe -s /mingw32/share/openocd/scripts -f /mingw32/share/openocd/scripts/interface/ftdi/um232h.cfg -f /mingw32/share/openocd/scripts/board/esp-wroom-32.cfg
    openocd.exe -s /mingw32/share/openocd/scripts -f /mingw32/share/openocd/scripts/interface/ftdi/um232h.cfg -f /mingw32/share/openocd/scripts/board/esp-wroom-32.cfg
    ;;
esac
