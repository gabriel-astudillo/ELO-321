#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int random_number(int min, int max){
    srand(getpid());

    int aleatorio = min + rand() % (max - min + 1);

    return aleatorio;
}


void mostrar_nodo(char nodo_id){
    printf("1) Nodo %c  PID=%d  PPID=%d\n", 
        nodo_id, getpid(), getppid());
    
    /*sleep(random_number(2,5));
    
    printf("2) Nodo %c  PID=%d  PPID=%d\n", 
        nodo_id, getpid(), getppid());*/
}

void prueba(){
    printf(">>>PID=%d,PPID=%d\n", getpid(), getppid());
}

int main(int argc, char* argv[]) {

    int fork_f1 = fork();

    if(fork_f1 > 0){ // (Nodo A) Proceso padre
        int fork_f2 = fork();
        
        if(fork_f2 > 0){ // (Nodo A) Proceso padre
            
            int fork_f3 = fork();
            
            if(fork_f3 > 0){ // (Nodo A) Proceso padre
                mostrar_nodo('A');
                wait(nullptr);
                wait(nullptr);
                wait(nullptr);
            }
            else if(fork_f3 == 0){ // (Nodo D) Proceso hijo
                mostrar_nodo('D');
                exit(EXIT_SUCCESS);
            }
            
            
            
        }
        else if(fork_f2 == 0){ // (Nodo C) Proceso hijo
            mostrar_nodo('C');
            exit(EXIT_SUCCESS);
        }
    }
    else if(fork_f1 == 0){ // (Nodo B) Proceso hijo 
        mostrar_nodo('B');
    }

    exit(EXIT_SUCCESS);
}






















