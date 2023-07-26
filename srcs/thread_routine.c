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
	time_since_eat = 0;
	pthread_mutex_lock(&philo->mutex_list->sync);
	pthread_mutex_unlock(&philo->mutex_list->sync);
	philo->startup_time = get_current_time();
	if (philo->philo_id % 2 == 1)
	{
		philo_think(philo, &time_since_eat);
		ft_usleep(10, philo, &time_since_eat);
	}
	while (philo->is_alive)
	{
		philo_eat(philo, &time_since_eat);
		philo_sleep(philo, &time_since_eat);
		philo_think(philo, &time_since_eat);
//		usleep(100);
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo, int *time_since_eat)
{
	int	action_time;

	take_fork(philo, philo->left_fork, time_since_eat);
	take_fork(philo, philo->right_fork, time_since_eat);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	action_time = get_time_since(philo->startup_time);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is eating\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	ft_usleep(philo->time_to_eat, philo, time_since_eat);
	pthread_mutex_unlock(&philo->left_fork->f_mutex);
	pthread_mutex_unlock(&philo->right_fork->f_mutex);
	if (philo->eat_goal != -1)
	{
		philo->eat_count++;
		if (philo->eat_goal == philo->eat_count)
			call_goal_achieve(philo);
	}

}

static void	philo_sleep(t_philo *philo, int *time_since_eat)
{
	int	action_time;

	(void)time_since_eat;
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	action_time = get_time_since(philo->startup_time);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is sleeping\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	printf("sleep time expected : %d\n", philo->time_to_sleep);
	ft_usleep(philo->time_to_sleep, philo, time_since_eat);
}

static void	philo_think(t_philo *philo, int *time_since_eat)
{
	int	action_time;

	(void)time_since_eat;
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	action_time = get_time_since(philo->startup_time);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d is thinking\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}

static void	take_fork(t_philo *philo, t_fork *fork, int *time_since_eat)
{
	int	action_time;

	(void)time_since_eat;
	pthread_mutex_lock(&fork->f_mutex);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	action_time = get_time_since(philo->startup_time);
	if (!philo->mutex_list->dead_philo_check)
		printf("%d %d has taken a fork\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}
