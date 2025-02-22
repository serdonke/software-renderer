#!/bin/bash

if [[ ! -d build ]]; then
    mkdir build
    echo "Build dir created"
else
    echo "Build dir exists"
fi

if [[ -f build/main.out ]]; then
    rm build/main.out
    echo "Removed build/main.out"
fi

if [[ -f build/out.png ]]; then
    rm build/out.png
    echo "Removed old build/out.png"
fi

gcc -Wall -Wextra src/main.c -o build/main.out
echo "Built main.out"

(cd build && ./main.out)
echo "Generated build/out.png"

echo "TADAAAAAAA"
feh build/out.png

