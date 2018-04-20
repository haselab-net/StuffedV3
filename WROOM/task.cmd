if "%1"=="monitor" (
	C:/msys32/mingw32.exe make monitor
)
if "%1"=="app-flash" (
	taskkill -f -im python.exe
	C:/msys32/mingw32.exe make %1
)
if "%1"=="app-run" (
	taskkill -f -im python.exe
	C:/msys32/mingw32.exe ./task.sh app-run
)
