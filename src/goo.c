#ifndef GOO_C_
#define GOO_C_

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#if !defined(WIDTH) && !defined(HEIGHT)
#  define WIDTH  1024
#  define HEIGHT 1024
#elif !defined(WIDTH) || !defined(HEIGHT)
#  error "define both WIDTH and HEIGHT!"
#endif

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

typedef struct {
    int32_t x;
    int32_t y;
} Point;

typedef struct {
    Point p0;
    Point p1;
    Point p2;
} Triangle;

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

void gooDrawLineNaive(uint8_t* surface, int32_t x0, int32_t y0, 
                                        int32_t x1, int32_t y1, Color color)
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

void gooDrawTriangleWireframe(uint8_t* surface, Triangle triangle, Color color)
{
    gooDrawLineNaive(surface, triangle.p0.x, triangle.p0.y, 
                     triangle.p1.x, triangle.p1.y, color);
    gooDrawLineNaive(surface, triangle.p1.x, triangle.p1.y, 
                     triangle.p2.x, triangle.p2.y, color);
    gooDrawLineNaive(surface, triangle.p2.x, triangle.p2.y, 
                     triangle.p0.x, triangle.p0.y, color);
}

void gooSortVerticesByY(Triangle* triangle) {
    if (triangle->p0.y > triangle->p1.y) {
        Point temp = triangle->p0;
        triangle->p0 = triangle->p1;
        triangle->p1 = temp;
    }
    if (triangle->p1.y > triangle->p2.y) {
        Point temp = triangle->p1;
        triangle->p1 = triangle->p2;
        triangle->p2 = temp;
    }
    if (triangle->p0.y > triangle->p1.y) {
        Point temp = triangle->p0;
        triangle->p0 = triangle->p1;
        triangle->p1 = temp;
    }
}

void gooDrawHorizontalLine(uint8_t* surface, int32_t xa, int32_t xb, int32_t y, Color color)
{
    // Make sure xa is left most point
    if (xa > xb) {
        uint32_t tmp = xa;
        xa = xb;
        xb = tmp;
    }

    for (int32_t x = xa; x <= xb; x++)
    {
        if (x >= WIDTH || y >= HEIGHT) continue;
        gooPutPixel(surface, x, y, color);
    }
    
}

void gooDrawTriangleScanline(uint8_t* surface, Triangle triangle, Color color)
{
    // NOTE:sort the points according to y coord
    // P0 < P1 < P2
    gooSortVerticesByY(&triangle);

    // Draw top half 
    // moving from p0 to p1
    for (int32_t start = triangle.p0.y; start <= triangle.p1.y; start++)
    {
        float t_long  = ((float)start - (float)triangle.p0.y) / ((float)triangle.p2.y - (float)triangle.p0.y);
        float t_short = ((float)start - (float)triangle.p0.y) / ((float)triangle.p1.y - (float)triangle.p0.y);

        int32_t x_long  = triangle.p0.x + lroundf(t_long * (triangle.p2.x - triangle.p0.x));
        int32_t x_short = triangle.p0.x + lroundf(t_short * (triangle.p1.x - triangle.p0.x));
        
        gooDrawHorizontalLine(surface, x_long, x_short, start, color);
    }
    // Draw bottom half
    for (int32_t middle = triangle.p1.y + 1; middle <= triangle.p2.y; middle++)
    {
        float t_long  = ((float)middle - (float)triangle.p0.y) / ((float)triangle.p2.y - (float)triangle.p0.y);
        float t_short = ((float)middle - (float)triangle.p1.y) / ((float)triangle.p2.y - (float)triangle.p1.y);

        int32_t x_long  = triangle.p0.x + lroundf(t_long * (triangle.p2.x - triangle.p0.x));
        int32_t x_short = triangle.p1.x + lroundf(t_short * (triangle.p2.x - triangle.p1.x));
        
        gooDrawHorizontalLine(surface, x_long, x_short, middle, color);
    }
}

#endif // GOO_C_

