#include "philo.h"

static void philo_eat(t_philo *philo);
static void philo_sleep(t_philo *philo);
static void philo_think(t_philo *philo);
static void	take_forks(t_philo *philo);

void	*thread_routine(void *thread)
{
	t_philo	*philo;

	philo = (t_philo*)thread;
	printf("thread %d launched\n", philo->philo_id);
	pthread_mutex_lock(&philo->mutex_list->sync);
	pthread_mutex_unlock(&philo->mutex_list->sync);
	philo->startup_time = get_current_time();
	if (philo->philo_id % 2 == 1)
	{
		philo_think(philo);
		msleep(10, philo);
	}
	int i = 0;
	while (philo->is_alive)
	{

		philo_think(philo);
		if (i == 5)
			call_death(philo);
		i++;
	}
	return (NULL);
}

static void philo_eat(t_philo *philo)
{
	int	action_time;

	take_forks(philo);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	action_time = get_current_time();
	printf("%d %d is eating...\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
	philo->time_of_last_meal = get_current_time();
	msleep(philo->time_to_eat,philo);
	philo->time_of_last_meal = get_current_time();
	philo->right_fork->fork_available = true;
	pthread_mutex_unlock(&philo->right_fork->f_mutex);
	philo->left_fork->fork_available = true;
	pthread_mutex_unlock(&philo->left_fork->f_mutex);
}


static void philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%d : %d is thinking\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}

static void	take_forks(t_philo *philo)
{
	int	action_time;

	while (!get_fork_availability(philo->right_fork) && !get_fork_availability(philo->left_fork))
		check_death(philo);
	pthread_mutex_lock(&philo->left_fork->f_mutex);
	pthread_mutex_lock(&philo->right_fork->f_mutex);
	philo->left_fork->fork_available = false;
	action_time = get_time_since(philo->startup_time);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%d %d has taken a fork\n", action_time, philo->philo_id);
	philo->right_fork->fork_available = false;
	printf("%d %d has taken a fork\n", action_time, philo->philo_id);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}
