#include "philo.h"

static void	take_fork(t_philo *philo, t_fork *fork);
static void	rest_fork(t_philo *philo, t_fork *fork);


void	*thread_routine(void *thread)
{
	t_philo			*philo;
	int				time;

	philo = (t_philo *)thread;

	while (42)
	{
		usleep(100);
	}
	return NULL;
}

static void	take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->f_mutex);
	fork->available = false;
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%d %d has taken a fork", get_elapsed_time(philo->initial_time),
		philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}

static void	rest_fork(t_philo *philo, t_fork *fork)
{
	fork->available = true;
	pthread_mutex_unlock(&fork->f_mutex);
}

static void	philo_eat(t_philo *philo)
{
	int	start_time;
	int	cur_time;

	start_time = get_initial_time();
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%d %d is eating", start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	cur_time = get_elapsed_time(start_time);
	while (cur_time < philo->time_left_eat)
		cur_time = get_elapsed_time(start_time);
}

static void	philo_sleep(t_philo *philo)
{
	int	start_time;
	int	cur_time;

	start_time = get_initial_time();
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%d %d is sleeping", start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	cur_time = get_elapsed_time(start_time);
	while (cur_time < philo->time_left_sleep)
		cur_time = get_elapsed_time(start_time);
}
