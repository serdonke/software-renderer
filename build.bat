@echo off
setlocal enabledelayedexpansion

if not exist build (
    mkdir build
    echo Build dir created
) else (
    echo Build dir exists
)

if exist build\main.exe (
    del build\main.exe
    echo Removed build\main.exe
)

if exist build\out.png (
    del build\out.png
    echo Removed old build\out.png
)

gcc -Wall -Wextra src/main.c -o build\main.exe
echo Built main.exe

pushd build
main.exe
popd

echo Generated build\out.png

echo TADAAAAAAA
start build\out.png
