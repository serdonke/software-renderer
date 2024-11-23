#include <stdint.h>
#ifndef PPM_C_
#define PPM_C_

void write_ppm(const char* filename, void* data, size_t height, size_t width)
{
    if (!data)
    {
        fprintf(stderr, "WHERE IS DA PIXEL DATA YOU LIL' BITCH??");
        return;
    }

    //TODO: implement filename functionality later
    
    printf("P6\n%zu %zu\n255\n", width, height);

    fwrite(data, sizeof(uint32_t), width * height, stdout);
}

#endif //PPM_C_
