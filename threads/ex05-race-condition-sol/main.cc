#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/random.h>


int64_t contador;

pthread_mutex_t mutex;

typedef struct {
    int id;
    int iteraciones;
} ThreadConfig;

// Función que modelo
// el comportamiento del dado
void* llenar(void *arg) {
	ThreadConfig *cfg = (ThreadConfig*)arg;
    //int id = cfg->id;
    int iteraciones = cfg->iteraciones;


    
    for (int i = 0; i < iteraciones; i++) {
        pthread_mutex_lock(&mutex);
        contador++;
        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}

void ejemplo(uint32_t total_threads){

    pthread_t*  th_llenar = (pthread_t*)malloc(total_threads*sizeof(pthread_t));
    ThreadConfig* config  = (ThreadConfig*)malloc(total_threads*sizeof(ThreadConfig));

    contador = 0;
    int64_t contador_esperado = 0;

    pthread_mutex_init(&mutex, NULL);
    
    for (size_t t= 0; t < total_threads; t++){
        config[t].id = t;
        config[t].iteraciones = 100000;

        contador_esperado += config[t].iteraciones;
        pthread_create(&th_llenar[t], nullptr, llenar, (void*)&config[t]);
    }

    for (size_t t= 0; t < total_threads; t++){
        pthread_join(th_llenar[t], nullptr);
    }

    printf("Esperado: %lld\n", contador_esperado);
    printf("Obtenido: %lld\n", contador);

}

int main(int argc, char* argv[]) {
    if(argc == 2){
        // argv[1] threads
        ejemplo(atoi(argv[1]));
    }

    exit(EXIT_SUCCESS);
}

