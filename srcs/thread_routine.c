#include "philo.h"

static int philo_eat(t_philo *philo);
static int philo_sleep(t_philo *philo);
static int philo_think(t_philo *philo);
static int take_forks(t_philo *philo);

void	*thread_routine(void *thread)
{
	t_philo	*philo;

	philo = (t_philo*)thread;
	pthread_mutex_lock(&philo->mutex_list->sync);
	pthread_mutex_unlock(&philo->mutex_list->sync);
	philo->startup_time = get_current_time();
	if (philo->philo_id % 2 == 1)
	{
		philo_think(philo);
		usleep(100);
	}
	while (philo->is_alive)
	{
		if (philo_eat(philo) == DEATH
		|| philo_sleep(philo) == DEATH)
			return (NULL);
		philo_think(philo);
	}
	return (NULL);
}

static int philo_eat(t_philo *philo)
{
	if (take_forks(philo) == DEATH)
		return (DEATH);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%lld %d is eating\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	philo->time_of_last_meal = get_current_time();
	if (msleep(philo->time_to_eat,philo) == DEATH)
		return (DEATH);
	pthread_mutex_lock(&philo->right_fork->f_mutex);
	philo->right_fork->fork_available = true;
	pthread_mutex_unlock(&philo->right_fork->f_mutex);
	pthread_mutex_lock(&philo->left_fork->f_mutex);
	philo->left_fork->fork_available = true;
	pthread_mutex_unlock(&philo->left_fork->f_mutex);
	if (philo->eat_goal > 0)
	{
		philo->eat_count++;
		if (philo->eat_count == philo->eat_goal)
		{
			pthread_mutex_lock(&philo->mutex_list->print_mutex);
			call_goal_achieve(philo);
		}
	}
	return (EXIT_SUCCESS);
}

static int philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%lld %d is sleeping\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	return (msleep(philo->time_to_sleep, philo));
}

static int philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%lld %d is thinking\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	return (EXIT_SUCCESS);
}

static int take_forks(t_philo *philo)
{
	while (!get_fork_availability(philo->right_fork) && !get_fork_availability(philo->left_fork))
	{
		if (check_death(philo)== DEATH)
			return (DEATH);
	}
	pthread_mutex_lock(&philo->left_fork->f_mutex);
	philo->left_fork->fork_available = false;
	pthread_mutex_unlock(&philo->left_fork->f_mutex);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%lld %d has taken a fork\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	pthread_mutex_lock(&philo->right_fork->f_mutex);
	philo->right_fork->fork_available = false;
	pthread_mutex_unlock(&philo->right_fork->f_mutex);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%lld %d has taken a fork\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	return (EXIT_SUCCESS);
}
