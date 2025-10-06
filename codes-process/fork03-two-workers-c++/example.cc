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

    // Estos prints son para visualizar si efectivamente se mantiene la coherencia
    // de la jerarquía.
    std::cout << ">> Proceso Hijo PID:" << miPID << ". Proceso Padre PID: " << parentPID << "\n";
    std::cout << ">> Proceso Hijo PID:" << miPID << ". Tiempo  de Lanzamiento: " << tiempoLanzamiento << "\n";

    // Simular lanzamiento
    sleep(tiempoLanzamiento); 

    // Mostrar valor del dado
    std::cout << "<< Proceso Hijo PID:" << miPID << ". Valor dado: " << valorDado << "\n";

    // Estos prints son para visualizar si efectivamente se mantiene la coherencia
    // de la jerarquía.
    parentPID = getppid();
    std::cout << "<< Proceso Hijo PID:" << miPID << ". Proceso Padre PID: " << parentPID << "\n";

}

int main(int argc, char* argv[]) {
    pid_t fA = fork();
    if (fA > 0) {  
        // Código EXCLUSIVO proceso padre
        pid_t miPID = getpid();
        std::cout << "Proceso Padre PID:" << miPID;
        std::cout <<". Proceso hijo creado con PID: " << fA << "\n";   
        
        pid_t fB = fork();
        /*if (fB > 0) {  
            // Código EXCLUSIVO proceso padre 
	        wait(nullptr);
        }
        else*/ 
        if (fB == 0) {  // Código EXCLUSIVO del proceso hijo (PID2)
            lanzarDado();
            exit(EXIT_SUCCESS);
        }

        wait(nullptr);  // Esperar a que cualquier hijo termine
        wait(nullptr);  // Esperar a que cualquier hijo termine
    }
    else if (fA == 0) {  // Código EXCLUSIVO del proceso hijo (PID1)
        lanzarDado();
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_SUCCESS);
}




