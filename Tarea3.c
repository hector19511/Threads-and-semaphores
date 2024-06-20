/*
Hector de león 19511
En el promer código puede observarse que las tareas no se ejecutan al asignar un
valor inicial
de 0, pues el semaphore espera a recibir una publicación, al mismo tiempo que el
main y el primer thread
estan esparando también.
En el segundo código, test_third_sem2 muestra como, al cambiar de valor de
semaphor, se encrementa el numero de
semaphores disponibles. Es por eso que, al ejecutarse los hilos, se muestra como
baja el numero de semaphores disponibles
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#define INIT_VALUE 0 // Para el valor inicial del semáforo
int val = 0;
void My_thread1(void *ptr); // prototipo
sem_t my_semaphore; // counting semaphore
void My_thread2(void *ptr){
char inputString;
printf("Por favor ingrese una letra: \n");
scanf("%c", &inputString);
//val = 1;
//printf("Por");
sem_post(&my_semaphore);
pthread_exit(0);
}
int main(void)
{
pthread_t thread1;
pthread_t thread2;
int counter = 0;
srand(time(NULL)); // inicializa semilla del generador de números aleatorios
// ¿Qué pasa si se usan otros valores iniciales?
sem_init(&my_semaphore, 0, INIT_VALUE);
pthread_create(&thread1, NULL, (void*)&My_thread1, (void *)&counter);
pthread_create(&thread2, NULL, (void*)&My_thread2, NULL);
while(counter < 20)
{
usleep(500000+rand()%1000001); // tiempo aleatorio entre 0.5 y 1.5
segundos
sem_wait(&my_semaphore);
counter++;
sem_post(&my_semaphore);
printf("ParentThread: %d \n", counter);
}
pthread_join(thread1, NULL); // espeara que que el hilo termine.
pthread_join(thread2, NULL);
return(0);
}
void My_thread1(void *ptr)
{
int *cont; // Notar que se podría usar el mismo nombre, pero de todos modos
// no sería la misma variable que la del main. Este es un puntero
local.
cont = (int *)ptr; // Con esto, el puntero apunta a la dirección de la
// variable del main.
while(*cont < 20)
{
usleep(500000+rand()%1000001); // tiempo aleatorio
sem_wait(&my_semaphore);
(*cont)++;
sem_post(&my_semaphore);
printf("My_thread1: %d \n", *cont);
}
pthread_exit(0);
}
