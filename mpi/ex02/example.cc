# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct {
    char valor[15]; // 14 dígitos + '\0'
} timeStamp_t;

timeStamp_t get_timeStamp(){
    timeStamp_t ts;
    time_t ahora = time(NULL);
    struct tm *t = localtime(&ahora);

    strftime(ts.valor, sizeof(ts.valor), "%Y%m%d%H%M%S", t);
    return ts;
}

int main(int argc, char* argv[]){
    int count;
    float data[100];
    int dest;
    int i;
    int ierr;
    int num_procs;
    int rank;
    MPI_Status status;
    int tag;
    float value[200];
    
    ierr = MPI_Init ( &argc, &argv );

    if ( ierr != 0 ){
        printf ( "\n" );
        printf ( "Ejemplo MPI:\n" );
        printf ( "  MPI_Init error.\n" );
        exit ( EXIT_FAILURE );
    }
    
    ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &rank );
    ierr = MPI_Comm_size ( MPI_COMM_WORLD, &num_procs );

    if(num_procs < 2){
        fprintf(stderr, "Debe ejecutar el programa con al menos 2 procesos\n");
        fprintf(stderr, "mpirun -n 2 %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /**
       Process 0 
    */
    if ( rank == 0 ) {
        timeStamp_t t0 = get_timeStamp();
        printf ( "%s P:%d  Ejemplo MPI: Processes disponibles: %d\n", t0.valor, rank,  num_procs );
    }

    if ( rank == 0 ) {
        tag = 55;

        timeStamp_t t0 = get_timeStamp();
        printf ( "%s P:%d Esperando datos.\n", t0.valor,  rank );

        ierr = MPI_Recv(value, 200, 
                               MPI_FLOAT, 
                               MPI_ANY_SOURCE, 
                               tag, 
                               MPI_COMM_WORLD, 
                               &status );

        ierr = MPI_Get_count(&status, 
                             MPI_FLOAT,
                             &count );
        
        t0 = get_timeStamp();
        printf("%s P:%d Recibieron %d elementos.\n", t0.valor,  rank, count );

        printf("%s P:%d value[5] = %f\n", t0.valor, rank, value[5] );
    }
    else if( rank == 1 ){
        timeStamp_t t0 = get_timeStamp();
        printf("%s P:%d - Creando datos para enviar al proceso 0.\n", t0.valor,  rank );

        for( i = 0; i < 100; i++ ) {
            data[i] = i;
        }

        dest = 0;
        tag = 55;
        ierr = MPI_Send(data,
                        100, 
                        MPI_FLOAT, 
                        dest, 
                        tag, 
                        MPI_COMM_WORLD );
        
        t0 = get_timeStamp();
        printf("%s P:%d - Datos enviados.\n", t0.valor,  rank );
    }
    else{
        timeStamp_t t0 = get_timeStamp();
        printf("%s P:%d - MPI sin asignar :()\n", t0.valor,  rank );
    }
    
    ierr = MPI_Finalize();
    if ( rank == 0 ) {
        timeStamp_t t0 = get_timeStamp();
        printf("%s P:%d - Ejemplo MPI: Finalización normal.\n", t0.valor,  rank );
      }
    
    
    exit(EXIT_SUCCESS);
}



