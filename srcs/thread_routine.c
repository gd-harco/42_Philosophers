#include "philo.h"

static void	philo_sleep(t_philo *philo);
static void	philo_eat(t_philo *philo, int *time_last_eat);
static void	take_fork(t_philo *philo, t_fork *fork);
static void	rest_fork(t_fork *fork);

void	*thread_routine(void *thread)
{
	t_philo	*philo;
	int		time_last_eat;

	philo = (t_philo *)thread;
	while (philo->is_alive)
	{
		if (philo->right_fork->available && philo->left_fork->available)
			philo_eat(philo, &time_last_eat);
		else
		{
			pthread_mutex_lock(&philo->mutex_list->print_mutex);
			printf("%d %d is thinking\n", get_elapsed_time(philo->initial_time),
				philo->philo_id);
			pthread_mutex_unlock(&philo->mutex_list->print_mutex);
			while (!philo->right_fork->available
				&& !philo->left_fork->available)
				usleep(1000);
			continue ;
		}
		philo_sleep(philo);
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo, int *time_last_eat)
{
	int	start_time;
	int	cur_time;

	take_fork(philo, philo->left_fork);
	take_fork(philo, philo->right_fork);
	start_time = get_initial_time();
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%d %d is eating\n", start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	cur_time = get_elapsed_time(start_time);
	while (cur_time < philo->time_left_eat)
		cur_time = get_elapsed_time(start_time);
	rest_fork(philo->left_fork);
	rest_fork(philo->right_fork);
	*time_last_eat = 0;
}

static void	philo_sleep(t_philo *philo)
{
	int	start_time;
	int	cur_time;

	start_time = get_initial_time();
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%d %d is sleeping\n", start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	cur_time = get_elapsed_time(start_time);
	while (cur_time < philo->time_left_sleep)
		cur_time = get_elapsed_time(start_time);
}

static void	take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->f_mutex);
	fork->available = false;
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%d %d has taken a fork\n", get_elapsed_time(philo->initial_time),
		philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}

static void	rest_fork(t_fork *fork)
{
	fork->available = true;
	pthread_mutex_unlock(&fork->f_mutex);
}
