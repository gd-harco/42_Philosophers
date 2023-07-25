#include "philo.h"

static void	philo_sleep(t_philo *philo);
static void	philo_eat(t_philo *philo);
static void	philo_think(t_philo *philo);
static void	take_fork(t_philo *philo, t_fork *fork);

void	*thread_routine(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	philo->time_left_death = philo->time_to_die;
	if (philo->philo_id % 2 == 1)
	{
		philo_think(philo);
		usleep(1000);
	}
	while (philo->is_alive)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	int	start_time;
	int	cur_time;
	int	action_time;
	int	time_buff;

	take_fork(philo, philo->left_fork);
	take_fork(philo, philo->right_fork);
	start_time = get_current_time();
	printf("time left %d\n", philo->time_left_eat);
	action_time = get_time_since(philo->startup_time);
	time_buff = start_time;
	philo->time_left_death -= get_time_since(time_buff);
	if (philo->time_left_death <= 0)
		call_death(philo);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is eating\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	cur_time = get_time_since(start_time);
	while (cur_time < philo->time_left_eat)
		cur_time = get_time_since(start_time);
	pthread_mutex_unlock(&philo->left_fork->f_mutex);
	pthread_mutex_unlock(&philo->right_fork->f_mutex);
	philo->time_left_death = philo->time_to_die;
}

static void	philo_sleep(t_philo *philo)
{
	int	start_time;
	int	cur_time;
	int	action_time;
	int	time_buff;

	start_time = get_current_time();
	time_buff = start_time;
	action_time = get_time_since(philo->startup_time);
	philo->time_left_death -= get_time_since(time_buff);
	if (philo->time_left_death <= 0)
		call_death(philo);
	time_buff = get_current_time();
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is sleeping\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	cur_time = get_time_since(start_time);
	while (cur_time < philo->time_left_sleep)
	{
		philo->time_left_death -= time_buff;
		time_buff = get_current_time();
		cur_time = get_time_since(start_time);
		if (philo->time_left_death <= 0)
			call_death(philo);
	}

}

static void	philo_think(t_philo *philo)
{
	int	action_time;

	action_time = get_time_since(philo->startup_time);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is thinking\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	philo->time_left_death -= get_time_since(action_time);
	if (philo->time_left_death <= 0)
		call_death(philo);
}

static void	take_fork(t_philo *philo, t_fork *fork)
{
	int	action_time;
	int	time_buff;

	action_time = get_time_since(philo->startup_time);
	time_buff = get_current_time();
	pthread_mutex_lock(&fork->f_mutex);
	philo->time_left_death -= get_time_since(time_buff);
	if (philo->time_left_death <= 0)
	{
		printf("take fork, fork id %d, philo id %d\n", fork->fork_id, philo->philo_id);
		call_death(philo);
	}
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d has taken a fork\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}
