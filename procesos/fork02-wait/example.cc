#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int random_number(int min, int max){
    srand(getpid());

    int aleatorio = min + rand() % (max - min + 1);

    return aleatorio;
}

void childTask(){
    int tiempo_computo;

    tiempo_computo = random_number(5, 15);
    
    printf("Simulando cómputo por %d segundos... ", tiempo_computo);
    fflush(stdout);
    sleep(tiempo_computo);
    printf("Fin del trabajo simulado.\n");
    fflush(stdout);
}

int main(int argc, char* argv[]) {

    int h0 = fork();
    
    if(h0 > 0) {     
        /**
         *  Código exclusivo padre
         */
         wait(nullptr);
    }
    else if(h0 == 0){ 
        /**
         *  Código exclusivo hijo
         */
        childTask();
    }

    exit(EXIT_SUCCESS);
}






















