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

    gooFill(image, 0, 0, 0);
    gooDrawLineNaive(image, 0, 0, 300, 300);
    gooDrawLineNaive(image, 393, 300, 500, 432);

    if(!stbi_write_png("out.png", WIDTH, HEIGHT, 3, image, WIDTH * 3))
    {
        fprintf(stderr, "Failed to write image to disk\n");
        return -2;
    }

    return 0;
}
