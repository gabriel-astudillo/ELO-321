/**
 * Ejemplo de comunicación en Anillo
 * Explicado en
 * https://mpi-notes.readthedocs.io/send-recv-simple/
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int dato_enviado, dato_recibido;
    MPI_Status estado;
 
    // Inicialización del ambiente paralelo
    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
 
    if(rank == 0){
        dato_enviado = 2*(rank+1);
        MPI_Send(&dato_enviado    // referencia al vector de elementos a enviar
                ,1                // tamaño del vector a enviar
                ,MPI_INT          // Tipo de dato que envias
                ,rank+1           // id del proceso destino
                ,0                // etiqueta
                ,MPI_COMM_WORLD); // Comunicador por el que se manda
 
    }else{
        MPI_Recv(&dato_recibido // Referencia al vector donde se almacenará lo recibido
                ,1              // tamaño del vector a recibir
                ,MPI_INT        // Tipo de dato que recibe
                ,rank-1         // id del proceso origen de la que se recibe
                ,0              // etiqueta
                ,MPI_COMM_WORLD // Comunicador por el que se recibe
                ,&estado);      // estructura del estado de la recepción
 
        int origen = estado.MPI_SOURCE;
        printf("Proceso %d> dato recibido: %d desde el proceso %d\n", rank, dato_recibido, origen);
        dato_enviado = 2*(rank+1);
        
        if(rank != size-1){
            MPI_Send(&dato_enviado, 1 ,MPI_INT ,rank+1 , 0 ,MPI_COMM_WORLD);
        }
    }
 
    MPI_Finalize();
    exit(EXIT_SUCCESS);
}