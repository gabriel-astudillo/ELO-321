#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <random>

int main(int argc, char* argv[]) {

    pid_t pid = fork();
    if (pid == -1) {  
        std::cerr << "Fork failed\n";
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) {  
        // Código EXCLUSIVO proceso padre
        pid_t miPID = getpid();
        std::cout << "Proceso Padre PID:" << miPID <<". Proceso hijo creado con PID: " << pid << "\n";      

        int returnCode;
        wait(&returnCode);  // Esperar a que cualquier hijo termine
    }
    else if (pid == 0) {  
        // Código EXCLUSIVO del proceso hijo
        pid_t miPID = getpid();
        pid_t parentPID = getppid();

        std::mt19937 mt(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, 5); 
        int workSimTime = dist(mt);  // Obtener un número aleatorio


        std::cout << "Proceso Hijo PID:" << miPID << ". Proceso Padre PID: " << parentPID << "\n";
        std::cout << "Proceso Hijo PID:" << miPID << ". workSimTime: " << workSimTime << "\n";

        // Simular carga de trabajo
        sleep(workSimTime); 

        parentPID = getppid();
        std::cout << "Proceso Hijo PID:" << miPID << ". Proceso Padre PID: " << parentPID << "\n";

        exit(EXIT_SUCCESS);
    }

    exit(EXIT_SUCCESS);
}


