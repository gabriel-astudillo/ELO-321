#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>
#include "ppm-lib.hh"

struct option options_l[] = {
    {"help",  no_argument,       0, 'h'},
    {"archivo",  required_argument, 0, 'a'},
    {0, 0, 0, 0} // Debe terminar con una fila vacía
};

void show_error(char* msg){
    fprintf(stderr, "%s\n", msg);
}

void show_use(char* argv[]){
    fprintf(stderr, "Uso: %s --archivo=<ARCHIVO> [--help]\n", argv[0]);
}

int main(int argc, char* argv[]) {

    int   help = 0;               // Por omisión, no se pide ayuda
    char* image_file = nullptr;   // Por omisión, el archivo de imagen es null

    // Ciclo para procesar los argumentos
    int c;
    while ((c = getopt_long(argc, argv, "ha:", options_l, NULL)) != -1) {
        switch (c) {
            case 'h':
                help = 1;
                break;
            case 'a':
                image_file = optarg;
                break;
            default:
                break;
        }

    }

    // Mostrar ayuda cuando se colocar la opcion help
    // o cuando falta un argumento que es obligatorio.
    if((image_file == nullptr) || (help == 1)){
        show_use(argv);
        exit(EXIT_FAILURE);
    }

    // Si todos los argumentos están ingresados,
    // se debe verificar que el archivo exista.
    if (access(image_file, F_OK) != 0){
        char msg[255];
        snprintf(msg, sizeof(msg), "Error al abrir el archivo %s", image_file);
        show_error(msg);
        exit(EXIT_FAILURE);
    }


    // Si el archivo existe, se abre asumiendo que es PPM
    int width  = 0;
    int height = 0;
    PPMImage *image = nullptr;

    image = read_ppm(image_file);
    // Si no es PPM, termina
    if(image == nullptr){
        char msg[255];
        snprintf(msg, sizeof(msg), "El archivo %s no es un archivo PPM.", image_file);
        show_error(msg);
        exit(EXIT_FAILURE);
    }

    width  = image->width;
    height = image->height;
    printf("width: %d, height: %d\n", width, height);


    exit(EXIT_SUCCESS);
}






















