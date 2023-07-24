#include "philo.h"


void	*thread_routine(void *thread_id)
{
	int	*id;
	pthread_mutex_t	print_mutex;

	pthread_mutex_init(&print_mutex, NULL);
	id = (int *)thread_id;
	pthread_mutex_lock(&print_mutex);
	printf ("Hello from thread %d\n", *id);
	pthread_mutex_unlock(&print_mutex);
	return (NULL);
}
