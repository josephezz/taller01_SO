#include <stdio.h>
#include <unistd.h>
#include <string.h>

/**
 * @file codigo2.c
 * @brief Compara printf() y write().
 */

/**
 * @brief Función principal.
 * @return 0 si funciona, 1 si write() falla.
 */
int main(void)
{
    const char *mensaje = "Mensaje escrito con printf() y luego con write().";

    printf("%s", mensaje);

    ssize_t resultado = write(STDOUT_FILENO, mensaje, strlen(mensaje));

    if (resultado == -1)
    {
        perror("Error al escribir con write");
        return 1;
    }

    return 0;
}