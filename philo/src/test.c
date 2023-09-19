#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *myturn(void *arg)
{
	while (1)
	{
		sleep(1);
		printf("mi turno\n");
	}
	return NULL;
}

void *youturn()
{
	while (1)
	{
		sleep(2);
		printf("tu turno\n");
	}
}

int main()
{
	pthread_t hilo1;

	pthread_create(&hilo1, NULL, myturn, NULL);
	//myturn();
	youturn();
}