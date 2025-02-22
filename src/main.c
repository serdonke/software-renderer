#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

#include "stb_image_write.h"

#include "goo.c"

int main(int argc, int argv[]) {
    size_t height = 512;
    size_t width  = 512;
    uint8_t* image = malloc(height * width * 3);
    if(!image) {
        fprintf(stderr, "Failed to allocate memory for the image\n");
        return -1;
    }

    gooFill(image, height, width, 255, 155, 55);

    if(!stbi_write_png("out.png", width, height, 3, image, width * 3))
    {
        fprintf(stderr, "Failed to write image to disk\n");
        return -2;
    }

    return 0;
}
