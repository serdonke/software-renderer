#ifndef OBJ_H
#define OBJ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    int a, b, c;
} Triangle;

#define MAX_VERTICES 10000
#define MAX_TRIANGLES 10000

static Vec3 vertices[MAX_VERTICES];
static Triangle triangles[MAX_TRIANGLES];
static int vertex_count = 0, triangle_count = 0;

void loadOBJ(const char* file) {
    FILE* fp = fopen(file, "r");
    if (!fp) {
        perror("Failed to open OBJ file");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == 'v' && line[1] == ' ') { // Vertex
            if (vertex_count < MAX_VERTICES) {
                sscanf(line, "v %f %f %f",
                       &vertices[vertex_count].x,
                       &vertices[vertex_count].y,
                       &vertices[vertex_count].z);
                vertex_count++;
            }
        } else if (line[0] == 'f') { // Face
            if (triangle_count < MAX_TRIANGLES) {
                int a, b, c;
                sscanf(line, "f %d %d %d", &a, &b, &c);
                triangles[triangle_count].a = a - 1; // Convert 1-based to 0-based
                triangles[triangle_count].b = b - 1;
                triangles[triangle_count].c = c - 1;
                triangle_count++;
            }
        }
    }

    fclose(fp);
}

#endif // OBJ_H

