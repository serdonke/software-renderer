#ifndef GOO_C_
#define GOO_C_

#include <stdint.h>

int gooFill(uint32_t* surface, size_t height, size_t width, uint32_t color)
{
    for (size_t i = 0; i < height * width; i++)
    {
        surface[i] = color;    
    }
    return 0;
}

#endif // GOO_C_

