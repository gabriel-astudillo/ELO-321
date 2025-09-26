#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    pid_t pid = fork();
    if (pid == -1) {  
        std::cerr << "Fork failed\n";
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {  
        // Código EXCLUSIVO del proceso hijo
        pid_t miPID = getpid();
        pid_t parentPID = getppid();
        std::cout << "Proceso Hijo PID:" << miPID << ". Proceso Padre PID: " << parentPID << "\n";
    }
    else if (pid > 0) {  
        // Código EXCLUSIVO proceso padre
        pid_t miPID = getpid();
        std::cout << "Proceso Padre PID:" << miPID <<". Proceso hijo creado con PID: " << pid << "\n";      
    }

    exit(EXIT_SUCCESS);
}

