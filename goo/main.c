#include <stdio.h>
#include <stdlib.h>

#include "ppm.c"
#include "goo.c"

int main(void)
{
    size_t height = 512;
    size_t width  = 512;
    uint32_t* image_data = malloc(height * width * sizeof(uint32_t));
    
    if (!image_data)
    {
        fprintf(stderr, "Memory allocation for image failed\n");
    }

    gooFill(image_data, height, width, 0x00ffffff); // RGBA format?
    write_ppm(NULL, image_data, height, width);
}
