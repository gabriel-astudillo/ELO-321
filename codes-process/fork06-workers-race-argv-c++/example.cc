#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <ctime>
#include <string>

std::string symbols = "+-*/%#@\\|-_{}[]()<>!&";

void worker(int id) {
    char symbol = symbols[id % symbols.length()];

    for (int i = 0; i < 1000000; ++i) {
        if(i % 100 == 0) {
            std::cout << symbol;
            std::cout.flush();
        } 
    }
    std::cout << std::endl;
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    const int numProcesses = 2;

    for (int id = 0; id < numProcesses; id++) {
        pid_t pid = fork();  // Crear un nuevo proceso

        if (pid < 0) {
            std::cerr << "Error al hacer fork.\n";
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            worker(id); 
        } 
    }

    // Esperar a que todos los procesos hijos terminen
    for (int id = 0; id < numProcesses; id++) {
        wait(nullptr);
    }
    exit(EXIT_SUCCESS);
}

