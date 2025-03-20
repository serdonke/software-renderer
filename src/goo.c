#ifndef GOO_C_
#define GOO_C_

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define WIDTH  1024
#define HEIGHT 1024

typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

Color GRUVBOX_BG      = {  40,  40,  40, 255 };  // Background
Color GRUVBOX_FG      = { 235, 219, 178, 255 };  // Foreground
Color GRUVBOX_RED     = { 204,  36,  29, 255 };  // Red
Color GRUVBOX_GREEN   = { 152, 151,  26, 255 };  // Green
Color GRUVBOX_YELLOW  = { 215, 153,  33, 255 };  // Yellow
Color GRUVBOX_BLUE    = {  69, 133, 136, 255 };  // Blue
Color GRUVBOX_PURPLE  = { 177,  98, 134, 255 };  // Purple
Color GRUVBOX_AQUA    = { 104, 157, 106, 255 };  // Aqua
Color GRUVBOX_ORANGE  = { 214,  93,  14, 255 };  // Orange

int8_t gooFill(uint8_t* surface, Color color)
{
    for (size_t i = 0; i < HEIGHT * WIDTH; i++)
    {
        surface[i * 4 + 0] = color.r;
        surface[i * 4 + 1] = color.g;
        surface[i * 4 + 2] = color.b;
        surface[i * 4 + 3] = color.a;
    }
    return 0;
}

// Convert (x, y) coordinate into 1D stride based coordinate
static inline uint32_t gooParsePixel(int32_t x, int32_t y)
{
    return y * WIDTH + x;
}

static inline void gooPutPixel(uint8_t* surface, int32_t x, int32_t y, Color color)
{
    uint32_t index = gooParsePixel(x, y) * 4;
    surface[index + 0] = color.r;
    surface[index + 1] = color.g;
    surface[index + 2] = color.b;
    surface[index + 3] = color.a;
}

void gooDrawLineNaive(uint8_t* surface, int32_t x0, int32_t y0, int32_t x1, int32_t y1, Color color)
{
    float step = 0.001;
    for(float t = 0.0; t < 1.0; t += step)
    {
        int32_t x = x0 + lroundf(t * (x1 - x0));
        int32_t y = y0 + lroundf(t * (y1 - y0));

        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) continue;

        gooPutPixel(surface, x, y, color); 
    }
}

#endif // GOO_C_

