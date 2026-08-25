#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "funciones.h"


int main(int argc, char *argv[])
{
    return mostrarProcesos();
    
}

int mostrarProcesos()
{
    pid_t pidHijo = getpid();
    pid_t pidPadre = getppid();

    char mensaje[100];

    int longitud = snprintf(mensaje, sizeof(mensaje), "PID del proceso hijo: %d\nPID del proceso padre: %d\n", pidHijo, pidPadre);

    if(write(STDOUT_FILENO, mensaje, longitud) == -1)
    {
        perror("Error al escribir con write");
        return 1;
    }
    return 6;
}