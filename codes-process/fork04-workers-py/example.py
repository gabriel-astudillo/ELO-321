import multiprocessing
import time
import os
import random
from datetime import datetime

def worker(num):
    pid = os.getpid()  # Obtener el PID del proceso actual

    # Generar tiempo de trabajo aleatorio
    workSimTime = random.randint(1, 10) 
    
    # Obtener la hora actual
    now = int(datetime.now().timestamp())
    print(f"{now} Proceso {num} (PID: {pid}) iniciado. Work time: {workSimTime}")

    
    time.sleep(workSimTime)  # Dormir por el tiempo aleatorio

    now = int(datetime.now().timestamp())
    print(f"{now} Proceso {num} (PID: {pid}) terminado.")

    exit(os.EX_OK)

if __name__ == "__main__":
    num_processes = 5
    processes = []

    for i in range(num_processes):
        p = multiprocessing.Process(target=worker, args=(i,))
        processes.append(p)
        p.start()  # Iniciar el proceso

    # Esperar a que todos los procesos terminen
    for p in processes:
        p.join()

    print("Todos los procesos han terminado.")

    exit(os.EX_OK)

    