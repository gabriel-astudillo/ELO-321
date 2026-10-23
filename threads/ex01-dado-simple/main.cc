#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/random.h>

typedef struct {
    int id;
    int caras;
} ThreadConfig;

void dormirMS(int ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (long)(ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
}

void timeStamp(char *buffer, size_t tamano) {
    struct timespec ts;
    // tiempo actual con precisión de nanosegundos
    clock_gettime(CLOCK_REALTIME, &ts);

    // Convertir segundos a hora local de forma thread-safe
    struct tm tm_info;
    localtime_r(&ts.tv_sec, &tm_info);

    // Extraer milisegundos de los nanosegundos
    int milisegundos = (int)(ts.tv_nsec / 1000000L);

    // Formatear: HH:MM:SS.mmm
    char tiempo_base[8+1];
    strftime(tiempo_base, sizeof(tiempo_base), "%H:%M:%S", &tm_info);

    snprintf(buffer, tamano, "%s.%03d", tiempo_base, milisegundos);
}

// Función que modelo
// el comportamiento del dado
void* modeloDado(void *arg) {
	ThreadConfig *cfg = (ThreadConfig*)arg;
    char ts[32];

    int caras = cfg->caras;
    int id = cfg->id;

    uint16_t semilla[3]; // semilla aleatoria de 48 bits
    getentropy(semilla, sizeof(semilla));

    int valor = erand48(semilla) * caras + 1;
    int dt    = erand48(semilla) * 10000 + 1000;
    
    timeStamp(ts, sizeof(ts));
    printf("%s [Dado %d] dt:  %d\n", ts, id, dt);
    dormirMS(dt);

    timeStamp(ts, sizeof(ts));
    printf("%s [Dado %d] valor:  %d\n", ts, id, valor);

    return NULL;
}

void caso_simple(){
    pthread_t dado;
    ThreadConfig config;

    config.id = 0;
    config.caras = 12;

    pthread_create(&dado, nullptr, modeloDado, (void*)&config);

    pthread_join(dado, nullptr);
}

int main(int argc, char* argv[]) {

    /**
     * Código cargador caso simple
     */
	caso_simple();

    exit(EXIT_SUCCESS);
}

