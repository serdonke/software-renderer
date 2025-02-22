#ifndef GOO_C_
#define GOO_C_

#include <stddef.h>
#include <stdint.h>

int gooFill(uint8_t* surface, size_t height, size_t width, uint8_t r, uint8_t g, uint8_t b)
{
    for (size_t i = 0; i < height * width; i++)
    {
        surface[i * 3 + 0] = r;
        surface[i * 3 + 1] = g;
        surface[i * 3 + 2] = b;
    }
    return 0;
}

#endif // GOO_C_

