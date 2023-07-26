#include "philo.h"

static void	philo_sleep(t_philo *philo, int *time_since_eat);
static void	philo_eat(t_philo *philo, int *time_since_eat);
static void	philo_think(t_philo *philo, int *time_since_eat);
static void	take_fork(t_philo *philo, t_fork *fork, int *time_since_eat);

void	*thread_routine(void *thread)
{
	t_philo	*philo;
	int		time_since_eat;

	philo = (t_philo *)thread;
	pthread_mutex_lock(&philo->mutex_list->sync);
	pthread_mutex_unlock(&philo->mutex_list->sync);
	if (philo->philo_id % 2 == 1)
	{
		philo_think(philo, &time_since_eat);
		usleep(1000);
	}
	while (philo->is_alive)
	{
		philo_eat(philo, &time_since_eat);
		philo_sleep(philo, &time_since_eat);
		philo_think(philo, &time_since_eat);
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo, int *time_since_eat)
{
	int	action_time;

	take_fork(philo, philo->left_fork, time_since_eat);
	take_fork(philo, philo->right_fork, time_since_eat);
	action_time = get_time_since(philo->startup_time);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is eating\n", action_time, philo->philo_id);
	ft_usleep(philo->tte, philo);
	if (philo->eat_goal != -1)
	{
		philo->eat_count++;
		if (philo->eat_goal == philo->eat_count)
			call_goal_achieve(philo);
	}
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	pthread_mutex_unlock(&philo->left_fork->f_mutex);
	pthread_mutex_unlock(&philo->right_fork->f_mutex);
}

static void	philo_sleep(t_philo *philo, int *time_since_eat)
{
	int	action_time;

	(void)time_since_eat;
	action_time = get_time_since(philo->startup_time);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is sleeping\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	ft_usleep(philo->tts, philo);
}

static void	philo_think(t_philo *philo, int *time_since_eat)
{
	int	action_time;

	(void)time_since_eat;
	action_time = get_time_since(philo->startup_time);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is thinking\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}

static void	take_fork(t_philo *philo, t_fork *fork, int *time_since_eat)
{
	int	action_time;

	(void)time_since_eat;
	action_time = get_time_since(philo->startup_time);
	pthread_mutex_lock(&fork->f_mutex);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d has taken a fork\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}
