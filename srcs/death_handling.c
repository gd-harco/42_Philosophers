#include "philo.h"


void	call_goal_achieve(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	philo->is_alive = false;
	philo->mutex_list->dead_philo_check = true;
	pthread_mutex_unlock(&philo->mutex_list->is_alive_mutex);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}


void	call_death(t_philo *philo)
{
	int	death_time;

	death_time = get_time_since(philo->startup_time);
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	printf("%d %d has died\n", death_time, philo->philo_id);
	pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	philo->mutex_list->dead_philo_check = true;
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

	i = -1;
	while (data->philos[++i])
		pthread_detach(data->philos[i]->thread);
	fork_free(data->forks);
	philos_free(data->philos);
	mutex_list_destroy(&data->mutex_list);
}
