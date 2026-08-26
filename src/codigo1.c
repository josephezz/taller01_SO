#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "funciones.h"

/**
 * @file codigo1.c
 * @brief Obtiene y muestra los PID del proceso y su padre.
 */

/**
 * @brief Función principal.
 * @param argc Cantidad de argumentos.
 * @param argv Argumentos del programa.
 * @return Código retornado por mostrarProcesos().
 */
int main(int argc, char *argv[])
{
    return mostrarProcesos();
}

/**
 * @brief Obtiene y muestra los PID de los procesos.
 * @return 6 si funciona, 1 si ocurre un error.
 */
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