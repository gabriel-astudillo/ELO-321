#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <random>

void lanzarDado(){
    pid_t miPID = getpid();
    pid_t parentPID = getppid();

    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 10); 
    int tiempoLanzamiento = dist(mt);  // Obtener un número aleatorio

    std::uniform_int_distribution<int> valor(1, 6); 
    int valorDado = valor(mt);  // Obtener un número aleatorio


    std::cout << ">> Proceso Hijo PID:" << miPID << ". Proceso Padre PID: " << parentPID << "\n";
    std::cout << ">> Proceso Hijo PID:" << miPID << ". Tiempo  de Lanzamiento: " << tiempoLanzamiento << "\n";

    // Simular carga de trabajo
    sleep(tiempoLanzamiento); 

    parentPID = getppid();
    std::cout << "<< Proceso Hijo PID:" << miPID << ". Valor dado: " << valorDado << "\n";
    std::cout << "<< Proceso Hijo PID:" << miPID << ". Proceso Padre PID: " << parentPID << "\n";

    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    if (pid > 0) {  
        // Código EXCLUSIVO proceso padre
        int returnCode;
        pid_t miPID = getpid();
        std::cout << "Proceso Padre PID:" << miPID <<". Proceso hijo creado con PID: " << pid << "\n";   
        
        pid_t pid2 = fork();
        if (pid2 > 0) {  
            // Código EXCLUSIVO proceso padre
            std::cout << "Proceso Padre PID:" << miPID <<". Proceso hijo creado con PID: " << pid2 << "\n";   
        }
        else if (pid2 == 0) {  // Código EXCLUSIVO del proceso hijo
            lanzarDado();
        }

        wait(&returnCode);  // Esperar a que cualquier hijo termine
        wait(&returnCode);  // Esperar a que cualquier hijo termine
    }
    else if (pid == 0) {  // Código EXCLUSIVO del proceso hijo
        lanzarDado();
    }

    exit(EXIT_SUCCESS);
}




