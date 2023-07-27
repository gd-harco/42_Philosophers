#include "philo.h"

static void philo_eat(t_philo *philo);
static void philo_sleep(t_philo *philo);
static void philo_think(t_philo *philo);
static void	take_forks(t_philo *philo);

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
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

static void philo_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%lld %d is eating\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	philo->time_of_last_meal = get_current_time();
	msleep(philo->time_to_eat,philo);
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
}

static void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%lld %d is sleeping\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	msleep(philo->time_to_sleep, philo);
}

static void philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%lld %d is thinking\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}

static void	take_forks(t_philo *philo)
{
	while (!get_fork_availability(philo->right_fork) && !get_fork_availability(philo->left_fork))
		check_death(philo);
	pthread_mutex_lock(&philo->left_fork->f_mutex);
	pthread_mutex_lock(&philo->right_fork->f_mutex);
	philo->left_fork->fork_available = false;
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%lld %d has taken a fork\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->left_fork->f_mutex);
	philo->right_fork->fork_available = false;
	printf("%lld %d has taken a fork\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	pthread_mutex_unlock(&philo->right_fork->f_mutex);

}
