//Chávez Delgado Jorge Luis
//El sig  algoritmo resuelve el problema y lo hace por turnos, cada filosofo cuenta
//con un tiempo definido para comer (tiempo que dure), 
//cuando termina, le cede el lugar al siguiente.
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t pal1, pal2, pal3, pal4, pal5;

void * codigoFilos1(){
        printf("Hola soy el filosofo 1 y estoy pensando\n");
        pthread_mutex_lock(&pal1);
        printf("Yo filos 1 voy a comer un poco\n");
        pthread_mutex_unlock(&pal1);
        pthread_mutex_init(&pal2, NULL);
}

void * codigoFilos2(){
        printf("Hola soy el filosofo 2 y estoy pensandon\n");
        pthread_mutex_lock(&pal2);
        printf("Yo filos 2 voy a comer un poco\n");
        pthread_mutex_unlock(&pal2);
        pthread_mutex_init(&pal3, NULL);
}

void * codigoFilos3(){
        printf("Hola soy el filosofo 3 y estoy pensando\n");
        pthread_mutex_lock(&pal3);
        printf("Yo filos 3 voy a comer un poco\n");
        pthread_mutex_unlock(&pal3);
        pthread_mutex_init(&pal4, NULL);
}

void * codigoFilos4(){
        printf("Hola soy el filosofo 4 y estoy pensando\n");
        pthread_mutex_lock(&pal4);
        printf("Yo filos 4 voy a comer un poco\n");
        pthread_mutex_unlock(&pal4);
        pthread_mutex_init(&pal5, NULL);
}

void * codigoFilos5(){
        printf("Hola soy el filosofo 5 y estoy pensando\n");
        pthread_mutex_lock(&pal5);
        printf("Yo filos 5 voy a comer un poco\n");
        pthread_mutex_unlock(&pal5);
        pthread_mutex_init(&pal1, NULL);
}


int main(){
     
     pthread_t filos1;
     pthread_t filos2;
     pthread_t filos3;
     pthread_t filos4;
     pthread_t filos5;

     pthread_mutex_init(&pal1, NULL);
  
     pthread_create(&filos1, NULL, codigoFilos1, NULL);
     pthread_create(&filos2, NULL, codigoFilos2, NULL);
     pthread_create(&filos3, NULL, codigoFilos3, NULL);
     pthread_create(&filos4, NULL, codigoFilos4, NULL);
     pthread_create(&filos5, NULL, codigoFilos5, NULL);


}

