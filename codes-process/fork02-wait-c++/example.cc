#include <iostream>
#include <random>

#include <sys/types.h>
#include <unistd.h>

void childMain(){
    pid_t miPID = getpid();

    std::random_device rd;  
    std::mt19937 mt(rd()); 
    std::uniform_int_distribution<int> dist(1, 10);

    int workTime = dist(mt);

    std::cout << ">>Proceso Hijo PID:" << miPID << ". Proceso Padre PID: " << getppid() << "\n";
    std::cout << ">>Proceso Hijo PID:" << miPID << ". Tiempo de trabajo: " << workTime << "\n";

    // Simular carga de trabajo
    sleep(workTime); 

    std::cout << "<<Proceso Hijo PID:" << miPID << ". Proceso Padre PID: " << getppid() << "\n";
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {

    pid_t pid = fork();
    
    if (pid > 0) { // Código EXCLUSIVO proceso padre
        pid_t miPID = getpid();
        std::cout << "Proceso Padre PID:" << miPID <<". Proceso hijo creado con PID: " << pid << "\n";      

        int returnCode;
        wait(&returnCode);  // Esperar a que cualquier hijo termine
    }
    else if (pid == 0) { 
        childMain();
    }
    
    exit(EXIT_SUCCESS);
}



/*
if (pid == -1) {  
        std::cerr << "Fork failed\n";
        exit(EXIT_FAILURE);
    }
    else 
*/