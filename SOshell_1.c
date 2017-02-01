/*SISTEMAS OPERATIVOS GRUPO 6

PROGRAMA CREADO POR:  CHÁVEZ DELGADO JORGE LUIS Y SÁNCHEZ ÁLVAREZ CÉSAR */

/* DESCRIPCIÓN : ESTE ALGORITMO HACE LLAMADAS AL SISTEMA  CON LAS FUNCIONES DE UN SHELL (INTERPRETE DE COMANDOS)
 EL SHELL RECONOCE COMANDOS UNIX SIMPLES CON O SIN ARGUMENTOS. */

/*ELABORACION DE UNA SHELL*/


#include  <stdio.h>  //Libreria que contiene funciones de cabeceras de entrada y salida
#include  <string.h>  // Libreria para capturar cadenas de texto, como es el uso de gets
#include  <stdlib.h>  //Libreria que contiene los prototipos de funciones de C para gestión de memoria dinámica, control de procesos y otras
#include  <sys/types.h> //Libreria que contiene funciones de busqueda y ordenamiento de directorios y manipulacion de archivos
#include  <unistd.h>   //Libreria que contiene funciones para el manejo de directorios y archivos.

#define p printf

void  verifica_linea(char *linea, char **argv) //Funcion para verificar el estado de la línea que ingresa el usuario
{
    while (*linea != '\0') {       /*Si no es el fin de la línea*/
        while (*linea == ' ' || *linea == '\t' || *linea == '\n')
            *linea++ = '\0';     /*Va a reemplazar cualquier tabulador o salto de línea por un espacio*/
    *argv++ = linea;          /*Guarda el argumento en la posición*/
        while (*linea != '\0' && *linea != ' ' &&
               *linea != '\t' && *linea != '\n')
     linea++;             /* Pasa al siguiente argumento*/
    }
    *argv = '\0';                 /*Marca el fin del argumento*/
}

void  ejecutar(char **argv)
{
    pid_t  pid; // un entero capaz de contener un pid ; definimos un tipo de dato para contener un pid
    int    estado; // definimos un entero
    pid = fork();   // llamamos a la función fork, la cual devolverá cero al programa ejecutado en el proceso hijo y el pid del proceso hijo al padre
    if (pid < 0) {     /* Creando el proceso hijo           */
        p("*** ERROR: La creación del proceso hijo ha fallado.\n"); // mensaje de error "proceso hijo a fallado"
        exit(1); //  sale despues del error
    }
    else if (pid == 0) {          /*  Para el proceso hijo         */
        if (execvp(*argv, argv) < 0) {     /* Ejecuta el comando */
            p("\n*** ERROR, comando inválido*** \n"); // error de comando invalido.
            exit(1); //sale del proceso
        }
    }
    else {                                  /* Para el padra*/
        while (wait(&estado) != pid)       /* Espera que termine el hijo */
            ;
    }
}

 int main(void)
{
    char  linea[512];             /* Arreglo tipo caracter para la línea de entrada */
    char  *argv[32];              /* Arreglo tipo caracter para los argumentos del comando*/
    
    while (1) {                   /* ciclo para capturar la linea */
        p(" root# ");     /*   PROMPT*/
        fflush(stdin);   //limpia el buffer para ingresar la linea
        scanf(" %[^\n]",linea);
	p("\n");  //imprime la linea
        verifica_linea(linea, argv);       /* Pasamos a la verificación de la línea*/
        if (strcmp(argv[0], "exit") == 0)  /* Si la linea dice: "exit" salimos de la shell*/
            exit(0); // sale del proceso
        ejecutar(argv);           /*Para otros casos entra a la función ejecutar*/
    }
    
}
