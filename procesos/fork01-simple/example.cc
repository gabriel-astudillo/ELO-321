#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    pid_t pid = fork();

    if (pid < 0) {  
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) {  
        // Código EXCLUSIVO del proceso padre
    }
    else if (pid == 0) {  
        // Código EXCLUSIVO proceso hijo
    }

    exit(EXIT_SUCCESS);
}



