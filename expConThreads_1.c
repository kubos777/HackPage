/*
	Programa hecho en ANSI C que implementa hilos y variables mutex para el cálculo
	de e^x por medio de una serie infinita con el algoritmo "productor-consumidor".

	Hecho por Daniel Vargas Castro para el grupo 6 de la materia de Sistemas Operativos
	de la Facultad de Ingeniería de la UNAM, semestre 2017-1.
*/

#include <stdio.h>
#include <pthread.h>
#include <math.h>

int x, N, n = 0;				//Declaración de variables globales para no hacerme bolas con apuntadores.
float xN, factN, resultado = 0.0;
pthread_mutex_t tomar, poner;	//Se declaran semaforos "tomar" y "poner" para implementar el algoritmo

void *calculaXN ();		//CONSUMIDOR. Función que calcula x^n.
void *calculaFactN ();	//PRODUCTOR. Función que calcula el factorial de n.
 
int main(int argc, char *argv[]) 
{
	int i;
	pthread_t hilo_productor, hilo_consumidor;	//Se declaran los hilos que calculan los valores sobre los que se trabajará.

	printf("\n\t\tEste programa calcula el valor de e^x\n\n");		//Interacciones con el usuario.
	printf("\t¿Qué valor deseas asignarle a la variable x?   ");
	scanf("%d", &x);
	printf("\n\t¿Para cuántos términos deseas calcular la serie? (entre 0 y 10):    ");
	scanf("%d", &N);

	if (N > 0 && N <= 10)					//Se verifica que el dato ingresado cumpla con los requisitos.
	{
		pthread_mutex_init(&tomar, NULL);	//Se inicializa el semáforo para bloquear la lectura de la región crítica.
		pthread_mutex_init(&poner, NULL);	//Se inicializa el semáforo para bloquear la escritura de la región crítica.

		pthread_mutex_unlock(&tomar);		//Se deshabilita la lectura de la región crítica.
		pthread_mutex_lock(&poner);			//Se habilita la escritura hacia la región crítica.
			
		pthread_create(&hilo_productor, NULL, (void*) calculaFactN, NULL); //Se crean y ejecutan los hilos.
		pthread_create(&hilo_consumidor, NULL, (void*) calculaXN, NULL);
		
		pthread_join(hilo_productor, NULL);		//Se espéra a que terminen los hilos.
		pthread_join(hilo_consumidor, NULL);	
			
		pthread_mutex_destroy(&tomar);				//Se borran de memoria los semáforos.
		pthread_mutex_destroy(&poner);		
		printf("\n\t\te^%d = %f\n", x, resultado);	//Impresión de resultado.
	}
	else
		printf("\n\t\tIngresaste un valor incorrecto.\n");

	return 0;
}

void *calculaXN () //CONSUMIDOR
{ 
	while (n < N)
	{
		pthread_mutex_lock(&poner); 	//Se bloquea la escritura a la región crítica.
		 
		xN = pow((double)x, (double)n); //Se calcula x^n y se almacena el valor en una variable global.
		n ++;							//Se incrementa n para calcular el siguiente término de la serie.

		pthread_mutex_unlock(&tomar);	//Se permite la escritura en la región crítica.

		resultado += xN/factN; 			//Se calcula un término y se realiza la suma de los valores calculados.
	}
	pthread_exit(0);
}

void *calculaFactN () //PRODUCTOR
{
	int i;
	while (n < N)
	{
		pthread_mutex_lock(&tomar);		//Se bloquea la lectura de la región crítica.
		
		factN = 1.0;
		for (i = 1; i <= n; i++)		//Se calcula el factorial de n y se almacena el valor en una variable global.
			factN *= i;

		pthread_mutex_unlock(&poner);	//Se permite la escritura de la región crítica.
	}
	pthread_exit(0);
}