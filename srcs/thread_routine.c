#include "philo.h"

static void philo_think(t_philo *philo);

void	*thread_routine(void *thread)
{
	t_philo	*philo;
	int		time_since_eat;

	philo = (t_philo*)thread;
	printf("thread %d launched\n", philo->philo_id);
	pthread_mutex_lock(&philo->mutex_list->sync);
	pthread_mutex_unlock(&philo->mutex_list->sync);
	philo->startup_time = get_current_time();
	if (philo->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&philo->mutex_list->print_mutex);
		printf("%d is odd\n", philo->philo_id);
		pthread_mutex_unlock(&philo->mutex_list->print_mutex);
		philo_think(philo);
		msleep(10, philo, &time_since_eat);
	}
	int i = 0;
	while (philo->is_alive)
	{
		philo_think(philo);
		msleep(2000, philo, &time_since_eat);
		if (i == 5)
			call_death(philo);
		i++;
	}
	return (NULL);
}

static void philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%d : %d is thinking\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}
