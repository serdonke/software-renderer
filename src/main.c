#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

#include "stb_image_write.h"

#include "goo.c"

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj_loader_c.h"

static void get_file_data(void* ctx, const char* filename, const int is_mtl,
                          const char* obj_filename, char** data, size_t* len) {
    (void)ctx; (void)is_mtl; (void)obj_filename;  // Unused params

    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        *data = NULL;
        *len = 0;
        return;
    }

    fseek(file, 0, SEEK_END);
    *len = ftell(file);
    fseek(file, 0, SEEK_SET);

    *data = malloc(*len + 1);
    if (!*data) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return;
    }

    fread(*data, 1, *len, file);
    (*data)[*len] = '\0';
    fclose(file);
}

void renderOBJ(uint8_t* image, const char* filename) {
    tinyobj_attrib_t attrib;
    tinyobj_shape_t* shapes = NULL;
    tinyobj_material_t* materials = NULL;
    size_t num_shapes, num_materials;

    tinyobj_attrib_init(&attrib);
    unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;

    if (tinyobj_parse_obj(&attrib, &shapes, &num_shapes, 
                          &materials, &num_materials, 
                          filename, get_file_data, 
                          NULL, flags) != TINYOBJ_SUCCESS) {
        fprintf(stderr, "Failed to load OBJ file: %s\n", filename);
        return;
    }

    printf("Loaded OBJ with %d vertices and %d faces\n", 
            (int)(attrib.num_vertices / 3), 
            (int)(attrib.num_faces / 3));

    for (size_t i = 0; i < attrib.num_faces; i += 3) {
        int indices[3] = {
            attrib.faces[i + 0].v_idx,
            attrib.faces[i + 1].v_idx,
            attrib.faces[i + 2].v_idx
        };

        for (int j = 0; j < 3; j++) {
            int v0 = indices[j];
            int v1 = indices[(j + 1) % 3];

            float x0 = attrib.vertices[v0 * 3 + 0];
            float y0 = attrib.vertices[v0 * 3 + 1];

            float x1 = attrib.vertices[v1 * 3 + 0];
            float y1 = attrib.vertices[v1 * 3 + 1];

            int sx0 = (int)((x0 + 1.0) * WIDTH / 2.0);
            int sy0 = HEIGHT - (int)((y0 + 1.0) * HEIGHT / 2.0);
            int sx1 = (int)((x1 + 1.0) * WIDTH / 2.0);
            int sy1 = HEIGHT - (int)((y1 + 1.0) * HEIGHT / 2.0);

            gooDrawLineNaive(image, sx0, sy0, sx1, sy1, GRUVBOX_GREEN);
        }
    }


    tinyobj_attrib_free(&attrib);
    free(shapes);
    free(materials);
}
int main(void) {
    uint8_t* image = malloc(HEIGHT * WIDTH * 4);
    if(!image)
    {
        fprintf(stderr, "Failed to allocate memory for the image\n");
        return -1;
    }

    gooFill(image, GRUVBOX_BG);
    renderOBJ(image, "../src/assets/african_head.obj");

    if (!stbi_write_png("out.png", WIDTH, HEIGHT, 4, image, WIDTH * 4)) {
        fprintf(stderr, "Failed to write image to disk\n");
        return -2;
    }

    return 0;
}
