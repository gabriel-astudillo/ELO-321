#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "ppm-lib.hh"


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
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int width  = 0;
    int height = 0;
    PPMImage *image = nullptr;

    image = read_ppm(argv[1]);

    if (rank == 0) {
        if (argc != 3) {
            fprintf(stderr, "Uso: mpirun -np <P> %s <input.ppm> <output.ppm>\n", argv[0]);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        image = read_ppm(argv[1]);
        if (!image) {
            fprintf(stderr, "Error: No se pudo leer el archivo PPM P3.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        width  = image->width;
        height = image->height;
        printf("width: %d, height: %d\n", width, height);
    }

    // 1. Difusión de dimensiones geométricas
    MPI_Bcast(&width , 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&height, 1, MPI_INT, 0, MPI_COMM_WORLD);

    

    // 2. Particionamiento del espacio de datos
    int *sendcounts = (int*)malloc(size * sizeof(int));
    int *displs     = (int*)malloc(size * sizeof(int));

    int base_rows = height / size;
    int rem_rows = height % size;
    int offset = 0;

    for (int i = 0; i < size; i++) {
        int rows = base_rows + (i < rem_rows ? 1 : 0);
        sendcounts[i] = rows * width * 3; // bytes
        displs[i] = offset;
        offset += sendcounts[i];
    }

    int local_bytes = sendcounts[rank];
    uint8_t *local_buf = (uint8_t*)malloc(local_bytes * sizeof(uint8_t));

    // Sincronización y medición del tramo paralelo
    MPI_Barrier(MPI_COMM_WORLD);
    double t_start = MPI_Wtime();

    // 3. Distribución
    MPI_Scatterv(rank == 0 ? image->data : NULL, sendcounts, displs,
                 MPI_UNSIGNED_CHAR, local_buf, local_bytes, MPI_UNSIGNED_CHAR,
                 0, MPI_COMM_WORLD);

    // 4. Cómputo local puntual (Ejemplo: Escala de Grises ITU-R BT.601)
    for (int i = 0; i < local_bytes; i += 3) {
        uint8_t r = local_buf[i];
        uint8_t g = local_buf[i + 1];
        uint8_t b = local_buf[i + 2];
        uint8_t y = (uint8_t)(0.299f * r + 0.587f * g + 0.114f * b);
        local_buf[i]     = y;
        local_buf[i + 1] = y;
        local_buf[i + 2] = y;
    }

    // 5. Recolección
    MPI_Gatherv(local_buf, local_bytes, MPI_UNSIGNED_CHAR,
                rank == 0 ? image->data : NULL, sendcounts, displs,
                MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    double t_end = MPI_Wtime();

    if (rank == 0) {
        printf("Procesos: %2d | Tiempo Paralelo (Comm+Calc): %.6f s\n", size, t_end - t_start);
        write_ppm(argv[2], width, height, image->data);
        free(image->data);
        free(image);
    }

    free(local_buf);
    free(sendcounts);
    free(displs);
    MPI_Finalize();

    exit(EXIT_SUCCESS);
}






















