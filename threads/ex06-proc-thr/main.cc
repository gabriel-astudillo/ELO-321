#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/random.h>


int64_t contador;

typedef struct {
    int id;
    int iteraciones;
} ThreadConfig;

void* llenar(void *arg) {
	ThreadConfig *cfg = (ThreadConfig*)arg;
    int id = cfg->id;
    int iteraciones = cfg->iteraciones;
    
    int contador_interno = 0;
    for (int i = 0; i < iteraciones; i++) {
        contador_interno++;
    }

    contador += contador_interno;
    return NULL;
}

void ejemplo(uint32_t total_threads){
    pthread_t  th_llenar[total_threads];
    ThreadConfig config[total_threads];

    contador = 0;
    
    for (size_t t= 0; t < total_threads; t++){
        config[t].id = t;
        config[t].iteraciones = 100000;
        pthread_create(&th_llenar[t], nullptr, llenar, (void*)&config[t]);
    }

    for (size_t t= 0; t < total_threads; t++){
        pthread_join(th_llenar[t], nullptr);
    }

    printf("Obtenido: %lld\n", contador);
}

int main(int argc, char* argv[]) {
    if(argc == 2){
        int threads = atoi(argv[1]);

        int fork_f1 = fork();

        if(fork_f1 > 0){
            ejemplo(threads);    
        }
        ejemplo(threads);
    }

    exit(EXIT_SUCCESS);
}

