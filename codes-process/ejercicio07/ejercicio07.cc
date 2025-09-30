#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <random>

std::time_t T0;

void makeNode(std::string id) {
    pid_t pid = getpid();  // Obtener el PID del proceso actual

    std::mt19937 mt(std::random_device{}());  // Generador Mersenne Twister
    std::uniform_int_distribution<int> dist(1, 10); 
    int workSimTime = dist(mt);  // Obtener un número aleatorio

    std::time_t now = std::time(nullptr) - T0;
    std::cout << "t=" << now << "s\t" << id;
    std::cout << " (PID: " << pid << ") iniciado. (PPID: " << getppid() << ")";
    std::cout << " Work time: " << workSimTime << " s.\n";

    // Simular trabajo
    sleep(workSimTime);  

    now = std::time(nullptr) - T0;
    std::cout << "t=" << now << "s\t" << id;
    std::cout << " (PID: " << pid << ") fin. (PPID: " << getppid() << ")\n";
}

int main(int argc, char* argv[]) {
    T0 = std::time(nullptr);

    int fA = fork(); 
    if(fA > 0){
        int fB = fork(); // B
        if(fB == 0){
            int fC = fork(); // C
            if(fC == 0){
                /* Código PID3 */
                makeNode("PID3");
                exit(0);
            }
            int fD = fork(); // D
            if(fD == 0){
            /* Código PID4*/
            makeNode("PID4");
            exit(0);
            }
            /* Código PID2*/
            makeNode("PID2");
            wait(nullptr); //wait PID4
            wait(nullptr); //wait PID3
            exit(0);
        }
        /* Código PID0*/
        makeNode("PID0");
        wait(nullptr); //wait PID2
        wait(nullptr); //wait PID1
        exit(0);
    }else if(fA == 0){
        /* Código PID1*/
        makeNode("PID1");
        exit(0);
    }
}

