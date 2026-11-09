#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

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
    fprintf(stderr, "Uso: mpirun -np <P> %s --archivo=<input.ppm> [--help]\n", argv[0]);
}



/**
 * @brief Calcula la distribución de franjas de filas 1D balanceando el residuo.
 * 
 * @param height     Alto total de la imagen en filas.
 * @param width      Ancho total de la imagen en píxeles.
 * @param size       Número total de procesos MPI.
 * @param sendcounts Arreglo pre-asignado de tamaño 'size' para almacenar bytes por proceso.
 * @param displs     Arreglo pre-asignado de tamaño 'size' para almacenar desplazamientos en bytes.
 */
void calcular_particion_1d(int height, int width, int size, 
                           int *sendcounts, int *displs) {
    int base_rows = height / size;
    int rem_rows  = height % size;
    int offset    = 0;
    int channels  = 3;  // RGB

    for (int i = 0; i < size; i++) {
        // Los primeros 'rem_rows' procesos asumen una fila adicional
        int rows = base_rows + (i < rem_rows ? 1 : 0);
        sendcounts[i] = rows * width * channels;
        displs[i]     = offset;
        offset       += sendcounts[i];
    }
}

int main(int argc, char* argv[]) {
    int   help = 0;                  // Por omisión, no se pide ayuda
    char* image_file_in = nullptr;   // Por omisión, el archivo de imagen es null
    char* image_file_out = nullptr; 

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int width  = 0;
    int height = 0;
    PPMImage *image = nullptr;

    if (rank == 0) {
        // Sólo el proceso principal reviso los argumentos de la CLI
        // Ciclo para procesar los argumentos
        int c;
        while ((c = getopt_long(argc, argv, "ha:", options_l, NULL)) != -1) {
            switch (c) {
                case 'h':
                    help = 1;
                    break;
                case 'a':
                    image_file_in = optarg;
                    break;
                default:
                    break;
            }

        }

        // Mostrar ayuda cuando se colocar la opcion help
        // o cuando falta un argumento que es obligatorio.
        if((image_file_in == nullptr) || (help == 1)){
            show_use(argv);
            MPI_Abort(MPI_COMM_WORLD, 1);
            exit(EXIT_FAILURE);
        }

        // Si todos los argumentos están ingresados,
        // se debe verificar que el archivo exista.
        if (access(image_file_in, F_OK) != 0){
            char msg[255];
            snprintf(msg, sizeof(msg), "Error al abrir el archivo %s", image_file_in);
            show_error(msg);
            MPI_Abort(MPI_COMM_WORLD, 1);
            exit(EXIT_FAILURE);
        }

        image = read_ppm(image_file_in);
        // Si no es PPM, termina
        if(image == nullptr){
            char msg[255];
            snprintf(msg, sizeof(msg), "El archivo %s no es un archivo PPM.", image_file_in);
            show_error(msg);
            MPI_Abort(MPI_COMM_WORLD, 1);
            exit(EXIT_FAILURE);
        }

        ////////////////////////////////////////////
        // Cambiar según indicaciones de la tarea
        image_file_out = strdup("salida.ppm"); 

        width  = image->width;
        height = image->height;
        printf("width: %d, height: %d\n", width, height);
    }

    // 1. Difusión de dimensiones geométricas
    

    // 2. Particionamiento del espacio de datos
    

    // Sincronización y medición del tramo paralelo
    
    // 3. Distribución
    

    // 4. Cómputo local puntual (Ejemplo: Escala de Grises ITU-R BT.601)
    

    // 5. Recolección
    


    MPI_Finalize();

    exit(EXIT_SUCCESS);
}






















