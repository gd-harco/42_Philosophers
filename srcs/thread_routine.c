#include "philo.h"

static void	philo_sleep(t_philo *philo);
static void	philo_eat(t_philo *philo, int *time_last_eat);
static void	philo_think(t_philo *philo);
static void	take_fork(t_philo *philo, t_fork *fork);

void	*thread_routine(void *thread)
{
	t_philo	*philo;
	int		time_last_eat;

	philo = (t_philo *)thread;
	if (philo->philo_id % 2 == 1)
	{
		philo_think(philo);
		usleep(1000);
	}
	while (philo->is_alive)
	{
		philo_eat(philo, &time_last_eat);
		philo_sleep(philo);
		philo_think(philo);
	}
	call_death(philo);
	return (NULL);
}

static void	philo_eat(t_philo *philo, int *time_last_eat)
{
	int	start_time;
	int	cur_time;
	int	action_time;

	take_fork(philo, philo->left_fork);
	take_fork(philo, philo->right_fork);
	action_time = get_elapsed_time(philo->initial_time);
	start_time = get_initial_time();
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is eating\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	cur_time = get_elapsed_time(start_time);
	while (cur_time < philo->time_left_eat)
		cur_time = get_elapsed_time(start_time);
	pthread_mutex_unlock(&philo->left_fork->f_mutex);
	pthread_mutex_unlock(&philo->right_fork->f_mutex);
	*time_last_eat = 0;
}

static void	philo_sleep(t_philo *philo)
{
	int	start_time;
	int	cur_time;
	int	action_time;

	start_time = get_initial_time();
	action_time = get_elapsed_time(philo->initial_time);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is sleeping\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	cur_time = get_elapsed_time(start_time);
	while (cur_time < philo->time_left_sleep)
		cur_time = get_elapsed_time(start_time);
}

static void	philo_think(t_philo *philo)
{
	int	action_time;

	action_time = get_elapsed_time(philo->initial_time);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is thinking\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}

static void	take_fork(t_philo *philo, t_fork *fork)
{
	int	action_time;

	pthread_mutex_lock(&fork->f_mutex);
	fork->available = false;
	action_time = get_elapsed_time(philo->initial_time);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d has taken a fork\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}
