#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct {
    int width;
    int height;
    unsigned char *data; // W * H * 3 bytes
} PPMImage;

PPMImage* read_ppm(const char *filename);
void write_ppm(const char *filename, int width, int height, const unsigned char *data);