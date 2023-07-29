#include "philo.h"

static int	philo_eat(t_philo *philo);
static int	philo_sleep(t_philo *philo);
static int	philo_think(t_philo *philo);
static int	take_forks(t_philo *philo);

void	*thread_routine(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	pthread_mutex_lock(&philo->mutex_list->sync);
	pthread_mutex_unlock(&philo->mutex_list->sync);
	gettimeofday(&philo->startup_time, NULL);
	philo->time_of_last_meal = philo->startup_time;
	if (philo->philo_id % 2 == 1)
	{
		philo_think(philo);
		usleep(1000);
	}
	pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	while (philo->mutex_list->dead_philo_check == false)
	{
		pthread_mutex_unlock(&philo->mutex_list->is_alive_mutex);
		if (philo_eat(philo) == DEATH
			|| philo_sleep(philo) == DEATH)
			return (NULL);
		philo_think(philo);
		pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	}
	pthread_mutex_unlock(&philo->mutex_list->is_alive_mutex);
	return (NULL);
}

static int	philo_eat(t_philo *philo)
{
	if (take_forks(philo) == DEATH)
		return (DEATH);
	print_action(philo, "is eating");
	gettimeofday(&philo->time_of_last_meal, NULL);
	if (msleep(philo->time_to_eat, philo) == DEATH)
	{
		pthread_mutex_unlock(&philo->right_fork->f_mutex);
		pthread_mutex_unlock(&philo->left_fork->f_mutex);
		return (DEATH);
	}
//	pthread_mutex_lock(&philo->right_fork->f_mutex);
//	philo->right_fork->fork_available = true;
	pthread_mutex_unlock(&philo->right_fork->f_mutex);
//	pthread_mutex_lock(&philo->left_fork->f_mutex);
//	philo->left_fork->fork_available = true;
	pthread_mutex_unlock(&philo->left_fork->f_mutex);
	if (philo->eat_goal > 0)
	{
		philo->eat_count++;
		if (philo->eat_count == philo->eat_goal)
			return (call_goal_achieve(philo), DEATH);
	}
	return (EXIT_SUCCESS);
}

static int	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	return (msleep(philo->time_to_sleep, philo));
}

static int	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
	return (EXIT_SUCCESS);
}

static int	take_forks(t_philo *philo)
{
//	while (!get_fork_availability(philo->right_fork) && !get_fork_availability(philo->left_fork))
//	{
//		if (check_death(philo)== DEATH)
//			return (DEATH);
//	}
//	pthread_mutex_lock(&philo->left_fork->f_mutex);
//	philo->left_fork->fork_available = false;
//	pthread_mutex_unlock(&philo->left_fork->f_mutex);
//	if (!philo->mutex_list->dead_philo_check)
//		print_action(philo, "has taken a fork");
//	pthread_mutex_lock(&philo->right_fork->f_mutex);
//	philo->right_fork->fork_available = false;
//	pthread_mutex_unlock(&philo->right_fork->f_mutex);
//	if (!philo->mutex_list->dead_philo_check)
//		print_action(philo, "has taken a fork");
	if (philo->philo_id % 2)
	{
		if (check_death(philo) == DEATH)
			return (DEATH);
		pthread_mutex_lock(&philo->left_fork->f_mutex);
		print_action(philo, "has taken a fork");
		if (check_death(philo) == DEATH)
		{
			pthread_mutex_unlock(&philo->left_fork->f_mutex);
			return (DEATH);
		}
		pthread_mutex_lock(&philo->right_fork->f_mutex);
		print_action(philo, "has taken a fork");
		if (check_death(philo) == DEATH)
		{
			pthread_mutex_unlock(&philo->left_fork->f_mutex);
			pthread_mutex_unlock(&philo->right_fork->f_mutex);
			return (DEATH);
		}
	}
	else
	{
		if (check_death(philo) == DEATH)
			return (DEATH);
		pthread_mutex_lock(&philo->right_fork->f_mutex);
		print_action(philo, "has taken a fork");
		if (check_death(philo) == DEATH)
		{
			pthread_mutex_unlock(&philo->right_fork->f_mutex);
			return (DEATH);
		}
		pthread_mutex_lock(&philo->left_fork->f_mutex);
		print_action(philo, "has taken a fork");
		if (check_death(philo) == DEATH)
		{
			pthread_mutex_unlock(&philo->left_fork->f_mutex);
			pthread_mutex_unlock(&philo->right_fork->f_mutex);
			return (DEATH);
		}
	}
	return (EXIT_SUCCESS);
}

void	print_action(t_philo *philo, char *action)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	gettimeofday(&time, NULL);
	time.tv_sec -= philo->startup_time.tv_sec;
	time.tv_usec -= philo->startup_time.tv_usec;
	pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%ld %d %s\n", (time.tv_sec * 1000
				+ time.tv_usec / 1000), philo->philo_id, action);
	pthread_mutex_unlock(&philo->mutex_list->is_alive_mutex);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}
