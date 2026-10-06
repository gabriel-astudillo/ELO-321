#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]){
    int rank, size;
    
    //int len;
    //char version[MPI_MAX_LIBRARY_VERSION_STRING];
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //MPI_Get_library_version(version, &len);
    
    //printf("Hello, world, I am %d of %d, (%s, %d)\n", rank, size, version, len);
    printf("Hola Mundo. Proceso id=%d. Total=%d\n", rank, size);
    

    MPI_Finalize();
    
    return 0;

}

