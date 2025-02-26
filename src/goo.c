#ifndef GOO_C_
#define GOO_C_

#include <stddef.h>
#include <stdint.h>
#include <math.h>

#define WIDTH  512
#define HEIGHT 512

int8_t gooFill(uint8_t* surface, uint8_t r, uint8_t g, uint8_t b)
{
    for (size_t i = 0; i < HEIGHT * WIDTH; i++)
    {
        surface[i * 3 + 0] = r;
        surface[i * 3 + 1] = g;
        surface[i * 3 + 2] = b;
    }
    return 0;
}

// Convert (x, y) coordinate into 1D stride based coordinate
uint32_t gooParsePixel(uint32_t x, uint32_t y)
{
    return y * WIDTH + x;
}

int8_t gooDrawLineNaive(uint8_t* surface, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
{
    float step = 0.001;
    for(float t = 0.0; t < 1.0; t += step)
    {
        uint32_t x = x0 + lroundf(t * (x1 - x0));
        uint32_t y = y0 + lroundf(t * (y1 - y0));

        if (x >= WIDTH || y >= HEIGHT)
            continue;

        uint32_t index = gooParsePixel(x, y) * 3;
        surface[index + 0] = 255;
        surface[index + 1] = 0;
        surface[index + 2] = 0;
    }
    return 0;
}


#endif // GOO_C_

