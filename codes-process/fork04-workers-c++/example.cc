#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <random>

void worker(int num) {
    pid_t pid = getpid();  // Obtener el PID del proceso actual

    std::mt19937 mt(std::random_device{}());  // Generador Mersenne Twister
    std::uniform_int_distribution<int> dist(1, 10); 
    int workSimTime = dist(mt);  // Obtener un número aleatorio

    std::time_t now = std::time(nullptr);
    std::cout << now << " Proceso " << num;
    std::cout << " (PID: " << pid << ") iniciado. (PPID: " << getppid() << ")";
    std::cout << " Work time: " << workSimTime << " s.\n";

    // Simular trabajo
    sleep(workSimTime);  

    now = std::time(nullptr);
    std::cout << now << " Proceso " << num;
    std::cout << " (PID: " << pid << ") terminado.\n";

    exit(EXIT_SUCCESS);  // Terminar el worker
}

int main(int argc, char* argv[]) {
    const int numProcesses = 3;

    for (int i = 0; i < numProcesses; ++i) {
        pid_t pid = fork();  // Crear un nuevo proceso

        if (pid < 0) {
            std::cerr << "Error al hacer fork.\n";
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Código del proceso hijo
            // en este caso, la función worker 
            // se ejecuta en el proceso hijo
            worker(i);
        } 
        // El proceso padre continúa el bucle para 
        // crear más procesos
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < numProcesses; ++i) {
        wait(nullptr);
    }

    std::cout << "Todos los procesos han terminado.\n";
    exit(EXIT_SUCCESS);
}

