import os

# Crear un nuevo proceso
pid = os.fork()

if pid < 0:
    # Error al crear el proceso
    print("Error al hacer fork")
    exit(1) # Posix código de término con error
elif pid == 0:
    # Código EXCLUSIVO del proceso hijo
    miPID = os.getpid()
    parentPID = os.getppid()
    print(f"Proceso hijo  PID: {miPID}. Proceso padre PID: {parentPID}")
elif pid > 0:
    # Código EXCLUSIVO del proceso padre
    miPID = os.getpid()
    print(f"Proceso padre PID: {miPID}. Proceso hijo creado con PID: {pid}")
    
exit(os.EX_OK) # Posix código de término normal

if __name__ == "__main__":
    pass

