#!/bin/bash

if [[ -d build ]]; then
    echo "Build dir exists"
else
    mkdir build
    echo "Build dir created"
fi

if [[ -f build/main.out ]]; then
    rm build/main.out
    echo "Removed build/main.out"
fi

if [[ -f build/out.ppm ]]; then
    rm build/out.ppm
    echo "Removed old out.ppm"
fi

gcc -Wall -Wextra src/main.c -o build/main.out
echo "Built main.out"

./build/main.out 
echo "Generated out.png"

echo "TADAAAAAAA"
feh out.png
