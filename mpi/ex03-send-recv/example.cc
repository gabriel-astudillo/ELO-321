#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int rank;
    
    MPI_Status estado;

    // Inicialización del ambiente paralelo
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
 
    //Envia y recibe mensajes
    int dato_enviado = 1974;
    int dato_recibido;
    
    MPI_Send(&dato_enviado //referencia al vector de elementos a enviar
            ,1 // tamaño del vector a enviar
            ,MPI_INT // Tipo de dato que envias
            ,rank // pid del proceso destino
            ,0 //etiqueta
            ,MPI_COMM_WORLD); //Comunicador por el que se manda
 
    MPI_Recv(&dato_recibido // Referencia al vector donde se almacenara lo recibido
            ,1 // tamaño del vector a recibir
            ,MPI_INT // Tipo de dato que recibe
            ,rank // pid del proceso origen de la que se recibe
            ,0 // etiqueta
            ,MPI_COMM_WORLD // Comunicador por el que se recibe
            ,&estado); // estructura informativa del estado
 
	int origen = estado.MPI_SOURCE;
    printf("Proceso %d> dato recibido: %d desde el proceso %d\n", rank, dato_recibido, origen);
 
    MPI_Finalize();
    exit(EXIT_SUCCESS);
}