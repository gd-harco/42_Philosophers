#include "philo.h"


void	*thread_routine(void *thread)
{
	t_philo			*philo;
	int				time;

	philo = (t_philo *)thread;
	while (42)
	{
		pthread_mutex_lock(&philo->mutex_list->print_mutex);
		time = get_elapsed_time(philo->initial_time);
		printf("Time elapsed in thead %d : %d ;;%p\n", philo->philo_id, time, thread);
		usleep(1000000);
		pthread_mutex_unlock(&philo->mutex_list->print_mutex);
		usleep(100);
	}
	return NULL;
}
