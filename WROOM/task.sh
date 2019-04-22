#!/bin/sh
case "$1" in
    "app-run") 
    make -j9 app-flash&&make -j9 monitor
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
