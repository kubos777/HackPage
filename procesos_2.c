/* Alumno: Chávez Delgado Jorge Luis
 Fecha: 23 de Agosto de 2016
 Materia: Sistemas Operativos, Gpo. 6

 El programa utiliza fork() para crear un proceso hijo que copie las variables
 del proceso padre. El proceso padre encuentra el elemento mayor dentro de un arreglo
 previamente definido dentro del código (como una variable global), y el proceso hijo
 encuentra el elemento menor dentro del mismo arreglo. Los valores encontrados son imprimidos
 respectivamente por ambos procesos.
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#define p printf
int nums[10] = {3,75,93, 16, 2048, 89, 1011, 4, 50};

int encMayor(){
	int mayor = nums[0];
	int i = 0;
	while(i < 10){
		if (mayor < nums[i]){
			mayor = nums[i];
		}

		i++;
	}
	return mayor;
}

int encMenor(){
	int menor = nums[0];
	int i = 0;
	while(i < 10){
		if (menor > nums[i]){
			menor = nums[i];
		}

		i++;
	}

	return menor;
}

int main()
{
	int pid;
	pid = fork();

	if(pid)
		p("Hola soy el padre, y el elemento mayor es:%d\n", encMayor());
	else
		p("Hola soy el hijo, y el elemento menor es: %d\n", encMenor());
}
