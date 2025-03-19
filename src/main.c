#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

#include "stb_image_write.h"

#include "goo.c"
#include "obj.h"

int main(void) {
    uint8_t* image = malloc(HEIGHT * WIDTH * 4);
    if(!image)
    {
        fprintf(stderr, "Failed to allocate memory for the image\n");
        return -1;
    }
    // welp blessings of using .sh file as a build system
    loadOBJ("../src/assets/untitled.obj");
    printf("Loaded file assets/untitled.obj with triangle count: %d\n", triangle_count);

    gooFill(image, GRUVBOX_BG);

    gooDrawLineNaive(image, WIDTH/2, HEIGHT/2, WIDTH, HEIGHT, GRUVBOX_RED);
    gooDrawLineNaive(image, WIDTH/2, HEIGHT/2, WIDTH/2, HEIGHT, GRUVBOX_BLUE);
    gooDrawLineNaive(image, WIDTH/2, HEIGHT/2, WIDTH, HEIGHT/2, GRUVBOX_GREEN);
    gooDrawLineNaive(image, WIDTH/2, HEIGHT/2, 0, 0, GRUVBOX_ORANGE);
    gooDrawLineNaive(image, WIDTH/2, HEIGHT/2, WIDTH/2, 0, GRUVBOX_PURPLE);
    gooDrawLineNaive(image, WIDTH/2, HEIGHT/2, WIDTH, 0, GRUVBOX_YELLOW);
    gooDrawLineNaive(image, WIDTH/2, HEIGHT/2, 0, HEIGHT/2, GRUVBOX_AQUA);
    gooDrawLineNaive(image, WIDTH/2, HEIGHT/2, 0, HEIGHT, GRUVBOX_FG);

    if(!stbi_write_png("out.png", WIDTH, HEIGHT, 4, image, WIDTH * 4))
    {
        fprintf(stderr, "Failed to write image to disk\n");
        return -2;
    }

    return 0;
}
