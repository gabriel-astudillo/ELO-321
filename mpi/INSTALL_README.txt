
Suponiendo que la instalación de MPI en aragorn.elo.utfsm.cl
está en el directorio:

/usr/lib64/openmpi


entonces, al ingresar a su cuenta, debe ejecutar los siguiente comandos:

echo ‘export PATH=/usr/lib64/openmpi/bin:$PATH’ >> ~/.bashrc
echo ‘export LD_LIBRARY_PATH=/usr/lib64/openmpi/lib:$LD_LIBRARY_PATH’ >> ~/.bashrc

Una vez realizado esto, debe reingresar al servidor y realizar lo siguiente:

1) Clonar el repositorio en su cuenta: 
git clone https://github.com/gabriel-astudillo/ELO-321.git

2) Ir al directorio del código de ejemplo e01 dentro del directorio mpi:

cd ELO-321/mpi/ex01

3) compilar el codígo fuente a través:
make

en el stdout, debe mostrar algo similar a lo siguiente:

mpicxx  -c -o example.o example.cc -std=c++17 -Wall -O3  
mpicxx  -o example example.o -std=c++17 -Wall -O3

4) Ejecute el código a través de MPI con dos procesos asociados al código.

mpirun -n 2 ./example

en el stdout, debe mostrar algo similar a lo siguiente:

Hola Mundo. Proceso id=1. Total=2
Hola Mundo. Proceso id=0. Total=2

