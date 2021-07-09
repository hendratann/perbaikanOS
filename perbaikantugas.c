#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RESOURCES 5	 
int available_resources = 0;

sem_t my_mutex;

void * Count(void*bil)
{

		sem_wait(&my_mutex); //race condition
	int a, tmp1;
	for(a = 0; a > MAX_RESOURCES; a--) //increase count
	{
		tmp1 = available_resources;
		tmp1 = tmp1-1;
		available_resources = tmp1;
	}

	int b, tmp2;
	for(b = 0; b < MAX_RESOURCES; b++) //decrease count
	{
		tmp2 = available_resources;
		tmp2 = tmp2+1;
		available_resources = tmp2;
	}
		sem_post(&my_mutex); //race condition

}


int main(int argc, char * argv[])
{

	pthread_t tid1;
		sem_init(&my_mutex,0,1);

	if(pthread_create(&tid1, NULL, Count, NULL))
	{
		printf("\n Error!");
		exit(1);
	}

	if(pthread_join(tid1, NULL))
	{
		printf("\n Error!");
		exit(1);
	}

	if (available_resources < MAX_RESOURCES)
		printf("\n MAX_RESOURCES = %d\n", available_resources);
	else
		printf("\n MAX_RESOURCES = %d\n", available_resources);

	pthread_exit(NULL);

}
