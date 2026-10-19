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

typedef struct {
    int id;
    int inicio;
    int fin;
} ThreadConfig;

// Función que modelo
// el comportamiento del dado
void* llenar(void *arg) {
	ThreadConfig *cfg = (ThreadConfig*)arg;
    int id = cfg->id;
    uint64_t inicio = cfg->inicio;
    uint64_t fin    = cfg->fin;


    uint16_t semilla[3]; // semilla aleatoria de 48 bits
    getentropy(semilla, sizeof(semilla));

    for(uint64_t idx= inicio; idx < fin; idx++){
        int valor = erand48(semilla) * 65535 + 1;
        vector[idx] = valor;
    }
    
    return NULL;
}

void caso_simple(uint64_t max_items){

    vector = (double*)malloc(max_items * sizeof(double));

    if (vector == nullptr) {
        fprintf(stderr, "Error: no se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }

    pthread_t th_llenar;
    ThreadConfig config;

    config.id = 0;
    config.inicio = 0;
    config.fin    = max_items;

    uint64_t t_inicio = get_time_us();
    pthread_create(&th_llenar, nullptr, llenar, (void*)&config);

    pthread_join(th_llenar, nullptr);
    uint64_t t_fin = get_time_us();

    uint64_t tiempo_transcurrido = t_fin - t_inicio;
    printf("Tiempo transcurrido: %llu us\n", (unsigned long long)tiempo_transcurrido);

}

int main(int argc, char* argv[]) {
    if(argc == 2){
        caso_simple(atoll(argv[1]));
    }

    exit(EXIT_SUCCESS);
}

