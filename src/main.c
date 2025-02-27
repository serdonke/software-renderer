#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

#include "stb_image_write.h"

#include "goo.c"

int main(void) {
    uint8_t* image = malloc(HEIGHT * WIDTH * 3);
    if(!image) {
        fprintf(stderr, "Failed to allocate memory for the image\n");
        return -1;
    }
    Color black = {0, 0, 0};
    Color red = {255, 0, 0};

    gooFill(image, black);
    gooDrawLineNaive(image, 0, 0, 300, 300, red);
    gooDrawLineNaive(image, 393, 300, 500, 432, red);

    if(!stbi_write_png("out.png", WIDTH, HEIGHT, 3, image, WIDTH * 3))
    {
        fprintf(stderr, "Failed to write image to disk\n");
        return -2;
    }

    return 0;
}
