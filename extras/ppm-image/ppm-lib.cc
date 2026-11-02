#include "ppm-lib.hh"


// Función auxiliar para ignorar comentarios (# ...) y espacios en formato P3
static void skip_comments(FILE *fp) {
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch)) continue;
        if (ch == '#') {
            while ((ch = fgetc(fp)) != EOF && ch != '\n');
        } else {
            ungetc(ch, fp);
            break;
        }
    }
}

PPMImage* read_ppm(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return NULL;

    char magic[3];
    skip_comments(fp);
    if (fscanf(fp, "%2s", magic) != 1 || magic[0] != 'P' || magic[1] != '3') {
        fclose(fp);
        return NULL;
    }

    PPMImage *img = (PPMImage*)malloc(sizeof(PPMImage));
    int maxval;
    skip_comments(fp);
    fscanf(fp, "%d", &img->width);
    skip_comments(fp);
    fscanf(fp, "%d", &img->height);
    skip_comments(fp);
    fscanf(fp, "%d", &maxval);

    size_t total_elements = (size_t)img->width * img->height * 3;
    img->data = (unsigned char*)malloc(total_elements * sizeof(unsigned char));

    for (size_t i = 0; i < total_elements; i++) {
        int val;
        skip_comments(fp);
        fscanf(fp, "%d", &val);
        img->data[i] = (unsigned char)val;
    }

    fclose(fp);
    return img;
}

void write_ppm(const char *filename, int width, int height, const unsigned char *data) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;

    fprintf(fp, "P3\n# Salida procesada con OpenMPI\n%d %d\n255\n", width, height);
    size_t total_elements = (size_t)width * height * 3;

    for (size_t i = 0; i < total_elements; i += 3) {
        fprintf(fp, "%d %d %d ", data[i], data[i + 1], data[i + 2]);
        if ((i / 3 + 1) % 6 == 0) fprintf(fp, "\n"); // Limita longitud de línea
    }
    fprintf(fp, "\n");
    fclose(fp);
}