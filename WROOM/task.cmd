if "%1"=="monitor" (
	taskkill -f -im python.exe
	C:/msys32/mingw32.exe make monitor
)
if "%1"=="app-flash" (
	taskkill -f -im python.exe
	C:/msys32/mingw32.exe make app-flash
)
