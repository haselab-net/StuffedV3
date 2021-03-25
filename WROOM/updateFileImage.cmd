set PATH=C:\msys32\usr\bin;C:\Home\espressif\esp\.espressif\python_env\idf4.2_py3.9_env\Scripts;%PATH%
set IDF_PATH=C:\Home\espressif\esp\v4.2\esp-idf

rem make disk images
cd filesystem
bash.exe -c "find.exe . -print | ../bin/mkespfsimage.exe -c 0 > ../build/espfs.img"
cd ..

rem bash.exe -c "./bin/mkspiffs.exe -c filesystem -b 4096 -p 256 -s 0x70000 build/spiffs.img"

rem flash images
python %IDF_PATH%\components\esptool_py\esptool\esptool.py write_flash --compress 0x3d0000 build/espfs.img
rem  0x210000 build/spiffs.img
