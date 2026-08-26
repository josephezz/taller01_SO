# Taller 01 - Llamadas al sistema

# Integrantes: Jose Alejandro Lopera - Danny Santiago Delgado Peralta

## Programa 1: Obtención de identificadores de proceso mediante llamadas al sistema

---

## Objetivo

Implementar un programa en lenguaje C que permita interactuar con el sistema operativo mediante llamadas al sistema.

El programa debe obtener el identificador del proceso actual y el identificador del proceso padre, además de realizar una escritura utilizando la llamada al sistema `write()` y verificar los posibles errores durante su ejecución.

---

# Implementación

Para desarrollar este programa se utilizaron diferentes funciones relacionadas con la interacción entre un programa en C y el sistema operativo Linux.

| Función | Tipo | Descripción |
|---|---|---|
| `getpid()` | Llamada al sistema | Permite obtener el identificador del proceso actual. |
| `getppid()` | Llamada al sistema | Permite obtener el identificador del proceso padre. |
| `write()` | Llamada al sistema | Permite escribir información directamente en la salida estándar. |
| `perror()` | Función de biblioteca | Permite mostrar información cuando ocurre un error durante la ejecución. |

---

# Funcionamiento del programa

El programa inicia desde la función `main()`, la cual ejecuta la función encargada de obtener y mostrar la información del proceso.

Primero se obtiene el identificador del proceso actual utilizando:

```c
pid_t pidHijo = getpid();
```

Esta llamada permite conocer el PID asignado por el sistema operativo al programa que se encuentra en ejecución(Denominado por nosotros como "Hijo").

Posteriormente, se obtiene el identificador del proceso padre mediante:

```c
pid_t pidPadre = getppid();
```

Esta función permite conocer cuál fue el proceso que inició la ejecución del programa actual.

Después de obtener estos valores, se genera un mensaje con la información obtenida y se utiliza la llamada al sistema:

```c
write()
```

para enviarlo directamente a la salida estándar.

---

# Manejo de errores

El programa verifica el valor de retorno de la llamada al sistema `write()`.

En caso de que la operación falle, se ejecuta:

```c
perror()
```

para mostrar la causa del error y finalizar la ejecución con un código de error.

Ejemplo:

```c
if(write(STDOUT_FILENO, mensaje, longitud) == -1)
{
    perror("Error al escribir con write");
    return 1;
}
```

Esto permite que el programa no continúe su ejecución cuando ocurre un fallo.

---

# Compilación

El programa fue compilado utilizando la opción `-Wall`, la cual permite mostrar advertencias generadas durante la compilación.

Comando utilizado:

```bash
gcc -Wall src/codigo1.c -Iinclude -o codigo1
```

Donde:

- `-Wall` permite mostrar advertencias del compilador.
- `src/codigo1.c` corresponde al archivo fuente del programa.
- `-Iinclude` indica la ubicación de los archivos de cabecera.
- `-o codigo1` define el nombre del archivo ejecutable.

---

# Ejecución

El programa se ejecuta mediante:

```bash
./codigo1
```

Resultado obtenido:

```text
PID del proceso hijo: 14839
PID del proceso padre: 11655
```

El primer valor corresponde al identificador del proceso actual y el segundo corresponde al proceso que inició su ejecución.

---

# Verificación del código de salida

El programa finaliza con un código de salida diferente de cero:

```c
return 6;
```

Este valor puede comprobarse utilizando el comando:

```bash
echo $?
```

Resultado obtenido:

```text
6
```

Esto permite comprobar que el programa devuelve correctamente el código definido por el desarrollador.

---

# Análisis

Durante la implementación se comprobó la diferencia entre una llamada al sistema y una función de biblioteca.

En este programa se utilizó `write()` debido a que permite realizar la escritura mediante una comunicación directa con el sistema operativo.

El flujo de ejecución es:

```
Programa en C
      |
      v
write()
      |
      v
Kernel de Linux
      |
      v
Salida estándar
```

Esto permite comprender cómo los programas pueden solicitar servicios directamente al sistema operativo mediante llamadas al sistema.

---

# Conclusión

La implementación permitió comprender el funcionamiento básico de las llamadas al sistema en Linux.

Mediante el uso de `getpid()`, `getppid()` y `write()` fue posible obtener información del proceso en ejecución y realizar una salida utilizando una llamada al sistema.

Además, la verificación del valor de retorno permitió comprobar que el programa no solamente funciona en condiciones normales, sino que también considera posibles errores durante su ejecución.


---

# Programa 2: Comparación entre printf() y write()

## Objetivo

Realizar un segundo programa que escriba el mismo mensaje utilizando primero `printf()` y después `write()`, con el objetivo de observar la diferencia entre una función de biblioteca y una llamada al sistema.

---

# Implementación

Para este programa se utilizó el siguiente mensaje:

```c
const char *mensaje = "Mensaje escrito con printf() y luego con write().";
```

Primero se utilizó:

```c
printf("%s", mensaje);
```

y posteriormente:

```c
write(STDOUT_FILENO, mensaje, strlen(mensaje));
```

No se utilizó `fflush()` ni se agregó un salto de línea al final del mensaje, siguiendo las indicaciones del taller.

Al principio esperábamos que el mensaje de `printf()` apareciera primero porque esa instrucción se encuentra antes en el código. Sin embargo, al ejecutar el programa se observó que el orden de salida no era el esperado.

---

# Prueba y observación

El programa se compiló utilizando:

```bash
gcc -Wall src/codigo2.c -o codigo2
```

Después se ejecutó con:

```bash
./codigo2
```

Durante la prueba se observó que `write()` podía mostrar su contenido antes que `printf()`, aunque `printf()` se ejecutaba primero.

Esto inicialmente generó confusión porque el orden de las instrucciones parecía indicar que `printf()` debía aparecer primero.

---

# Análisis

Después de revisar el funcionamiento de las dos funciones, se comprendió que `printf()` es una función de biblioteca que utiliza un búfer para manejar la salida.

Como no se utilizó `fflush()` y el mensaje no termina con un salto de línea, el texto escrito con `printf()` puede permanecer temporalmente en ese búfer.

Por otro lado, `write()` realiza una llamada al sistema para escribir en la salida estándar. Por esta razón, su mensaje puede aparecer antes.

El orden observado se puede representar de la siguiente manera:

```text
printf()
   |
   v
Búfer de la biblioteca
   |
   |
write()
   |
   v
Kernel
   |
   v
Salida estándar
```

Cuando el programa termina, el contenido pendiente del búfer de `printf()` puede ser enviado a la salida.

---

# Manejo de errores

También se verificó el valor de retorno de `write()`:

```c
if (resultado == -1)
{
    perror("Error al escribir con write");
    return 1;
}
```

Si la llamada falla, `perror()` muestra la causa del error y el programa termina con un código diferente de cero.

---

# Conclusión

La prueba permitió comprobar que `printf()` y `write()` no funcionan de la misma manera.

Aunque `printf()` aparece primero en el código, su contenido puede quedar temporalmente almacenado en un búfer. `write()`, en cambio, realiza la escritura mediante el sistema operativo.

La observación inicial no coincidió con lo que esperábamos, pero permitió entender mejor la diferencia entre una función de biblioteca y una llamada al sistema y la importancia del búfer de salida.
