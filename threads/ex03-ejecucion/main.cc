#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/random.h>

uint64_t get_time_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((uint64_t)ts.tv_sec * 1000000ULL) + ((uint64_t)ts.tv_nsec / 1000ULL);
}

uint64_t get_time_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((uint64_t)ts.tv_sec * 1000000000ULL) + (uint64_t)ts.tv_nsec;
}


double *vector;
double prueba;

typedef struct {
    int id;
    int partes;
    int total_elementos;
} ThreadConfig;

// Función que modelo
// el comportamiento del dado
void* llenar(void *arg) {
	ThreadConfig *cfg = (ThreadConfig*)arg;
    int id = cfg->id;
    int partes = cfg->partes;
    int total_elementos = cfg->total_elementos;
    
    uint64_t inicio = id*total_elementos/partes;
    uint64_t fin    = inicio + total_elementos/partes;


    uint16_t semilla[3]; // semilla aleatoria de 48 bits
    getentropy(semilla, sizeof(semilla));

    for(size_t idx= inicio; idx < fin; idx++){
        int valor = erand48(semilla) * 65535 + 1;
        vector[idx] = valor;
    }
    
    return NULL;
}

void caso_general(uint64_t max_items, uint32_t total_threads){

    vector = (double*)malloc(max_items * sizeof(double));

    if (vector == nullptr) {
        fprintf(stderr, "Error: no se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }

    pthread_t*  th_llenar = (pthread_t*)malloc(total_threads*sizeof(pthread_t));
    ThreadConfig* config  = (ThreadConfig*)malloc(total_threads*sizeof(ThreadConfig));
    
    uint64_t t_inicio = get_time_us();
    for (size_t t= 0; t < total_threads; t++){
        config[t].id = t;
        config[t].partes = total_threads;
        config[t].total_elementos = max_items;
        
        pthread_create(&th_llenar[t], nullptr, llenar, (void*)&config[t]);
    }

    for (size_t t= 0; t < total_threads; t++){
        pthread_join(th_llenar[t], nullptr);
    }
    
    uint64_t t_fin = get_time_us();

    uint64_t tiempo_transcurrido = t_fin - t_inicio;
    printf("Tiempo transcurrido: %llu us\n", (unsigned long long)tiempo_transcurrido);

}

int main(int argc, char* argv[]) {
    prueba = 0.0;
    if(argc == 3){
        // argv[1] total elementos
        // argv[2] threads
        caso_general(atoll(argv[1]), atoi(argv[2]));
    }

    exit(EXIT_SUCCESS);
}

