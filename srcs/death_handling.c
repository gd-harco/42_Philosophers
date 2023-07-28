#include "philo.h"


void	call_goal_achieve(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	philo->is_alive = false;
	pthread_mutex_unlock(&philo->mutex_list->is_alive_mutex);

	philo->mutex_list->dead_philo_check = true;
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}


void	call_death(t_philo *philo)
{

	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	if (!philo->mutex_list->dead_philo_check)
		printf("%lld %d died\n", get_time_since(philo->startup_time), philo->philo_id);
	pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	philo->mutex_list->dead_philo_check = true;
	philo->is_alive = false;
	pthread_mutex_unlock(&philo->mutex_list->is_alive_mutex);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}

void	fork_free(t_fork *forks)
{
	t_fork	*current;
	t_fork	*next;

	current = forks;
	while (current)
	{
		next = current->next;
		pthread_mutex_destroy(&current->f_mutex);
		free(current);
		current = next;
	}
}

void	philos_free(t_philo **philo)
{
	int	i;

	i = -1;
	while (philo[++i])
		free(philo[i]);
	free(philo);
}

void	mutex_list_destroy(t_mutex_list *mutex_list)
{
	pthread_mutex_destroy(&mutex_list->print_mutex);
	pthread_mutex_destroy(&mutex_list->is_alive_mutex);
}

void	exit_death(t_data *data)
{
	int	i;

	i =-1;
	while (data->philos[++i])
		pthread_join(data->philos[i]->thread, NULL);
	fork_free(data->forks);
	philos_free(data->philos);
	mutex_list_destroy(&data->mutex_list);
}

int	check_death(t_philo *philo)
{
	t_ms	current_time;

	current_time = get_current_time();
	if (current_time - philo->time_of_last_meal >= philo->time_to_die)
	{
		call_death(philo);
		return (DEATH);
	}
	return (0);
}
