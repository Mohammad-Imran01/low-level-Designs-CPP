# Use Windows-compatible commands
SHELL = cmd.exe

default: run

configure:
	cmake -S . -B ./build

build: configure
	cmake --build ./build

run: 
	.\build\src\Debug\LowLevelCppDesigns.exe

clean:
	if exist .\build rmdir /s /q .\build   