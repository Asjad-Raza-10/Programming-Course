#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t print_lock;

void *thread_print(void *arg)
{
	int id = *(int *) arg;
	pthread_mutex_lock(&print_lock);
	for (int i = 1; i <= 3; i++)
	{
		printf("Thread %d printing: %d\n", id, i);
		sleep(1);
	}
	pthread_mutex_unlock(&print_lock);
	return NULL;
}

int main()
{
	pthread_t t1, t2, t3;
	int id1 = 1, id2 = 2, id3 = 3;

	pthread_mutex_init(&print_lock, NULL);
	pthread_create(&t1, NULL, thread_print, &id1);
	pthread_create(&t2, NULL, thread_print, &id2);
	pthread_create(&t3, NULL, thread_print, &id3);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	pthread_mutex_destroy(&print_lock);
	return 0;
}
