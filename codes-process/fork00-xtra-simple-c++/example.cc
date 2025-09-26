#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    pid_t miPID = getpid();

    std::cout << "Hola mundo. PID=" << miPID << "\n";
    
    int inti = fork();

    miPID = getpid();
    if (inti == 0){
        std::cout << "HIJO: Hola mundo. PID=" << miPID << "\n";
    }
    else{
        std::cout << "PADRE: Hola mundo. PID=" << miPID << "\n";
    }
    

    exit(EXIT_SUCCESS);
}

