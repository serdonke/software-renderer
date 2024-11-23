#!/bin/bash

# Check if 'build' directory exists, create it if not
if [[ -d build ]]; then
    echo "Build dir exists"
else
    mkdir build
    echo "Build dir created"
fi

# Check if main.out exists, remove it if found
if [[ -f build/main.out ]]; then
    rm build/main.out
    echo "Removed build/main.out"
fi

if [[ -f build/out.ppm ]]; then
    rm build/out.ppm
    echo "Removed old out.ppm"
fi

# Compile main.c 
gcc -Wall -Wextra main.c -o build/main.out
echo "Built main.out"

# Run the program and generate the out.ppm file
./build/main.out > build/out.ppm
echo "Generated out.ppm"

# Display the generated image using feh
echo "TADAAAAAAA"
feh build/out.ppm
