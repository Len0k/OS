#include <stdio.h>
#include <pthread.h>

void *g(void *);
extern int counter = 0;
extern int t = 0;

int main()
{
	pthread_t t1, t2;
	int i = 1;
	pthread_create(&t1, NULL, g, (void *)i);
	i = i + 1;
	pthread_create(&t2, NULL, g, (void *)i);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf ("Counter value = %d\n", counter);
	return 0;
}
