#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <mpi.h>

int main(int argc, char *argv[]) { 
    int n;    // Número de iteraciones
	int	rank; // Identificador de proceso
	int	size; // Numero de procesos

    double PI25DT = 3.141592653589793238462643;
    double mypi; // Valor local de PI
	double pi;   // Valor globarl de PI
	double h;    // Aproximacion del area para el calculo de PI
	double sum;  // Acumulador para la suma del area de PI
 
    MPI_Init(&argc, &argv); // Inicializamos los procesos
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero total de procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador
 
    // Solo el proceso 0 va a conocer el numero de iteraciones que vamos a
    // ejecutar para la aproximacion de PI
	if (rank == 0) {
        if(argc != 2){
            fprintf(stderr, "Uso: mpirun -n <nro_proc> %s <iteraciones>\n", argv[0]);
            MPI_Finalize(); 
            exit(EXIT_FAILURE);
        }
		
        n = atoi(argv[1]);

        if (n <= 0){
            MPI_Finalize();
            exit(EXIT_FAILURE);
	    }
	}
 
	// El proceso 0 reparte al resto de procesos el numero de iteraciones
	// que calcularemos para la aproximacion de PI
	MPI_Bcast(&n, // Puntero al dato que vamos a enviar
	            1,  // Numero de datos a los que apunta el puntero
                MPI_INT, // Tipo del dato a enviar
                0, // Identificacion del proceso que envia el dato
                MPI_COMM_WORLD);  
	
    // Calculo de PI
    h = 1.0 / (double) n;
    sum = 0.0;
    for (int i = rank + 1; i <= n; i += size) {
        double x = h * ((double)i - 0.5);
        sum += (4.0 / (1.0 + x*x));
    }
    mypi = h * sum;

    // Todos los procesos ahora comparten su valor local de PI,
    // lo hacen reduciendo su valor local a un proceso
    // seleccionada a traves de una operacion aritmetica.
    MPI_Reduce(&mypi, // Valor local de PI
                &pi,  // Dato sobre el que vamos a reducir el resto
                1,	  // Numero de datos que vamos a reducir
                MPI_DOUBLE,  // Tipo de dato que vamos a reducir
                MPI_SUM,  // Operacion que aplicaremos
                0, // proceso que va a recibir el dato reducido
                MPI_COMM_WORLD);   

    // Solo el proceso 0 muestra el mensaje, ya que es el único que
    // conoce el valor de PI aproximado.
    if (rank == 0)
        printf("Valor aprox de PI: %f, error: %f\n", pi, fabs(pi - PI25DT));
 
    MPI_Finalize(); 
    exit(EXIT_SUCCESS); 
}