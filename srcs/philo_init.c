#include "philo.h"

int		create_philos(t_data *data);
void	create_one_philo(t_philo **philo, t_data *data, int i);

int	init_philo_fork(t_data *data)
{
	if (create_forks(data) == EXIT_FAILURE
		|| create_philos(data) == EXIT_FAILURE)
		return (exit_free_data(data));
	return (EXIT_SUCCESS);
}

int	create_philos(t_data *data)
{
	t_philo	**philo;
	size_t	i;

	philo = malloc(sizeof(t_philo *) * data->nb_of_philo + 1);
	if (!philo)
		return (EXIT_FAILURE);
	data->philos = philo;
	i = -1;
	while (++i < data->nb_of_philo)
	{
		philo[i + 1] = NULL;
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (EXIT_FAILURE);
		create_one_philo(philo, data, i);
	}
	philo[i] = NULL;
	philo[0]->right_fork = philo[i - 1]->left_fork;
	return (EXIT_SUCCESS);
}

void	create_one_philo(t_philo **philo, t_data *data, int i)
{
	t_fork	*forks;

	forks = data->forks;
	philo[i]->philo_id = i + 1;
	philo[i]->is_alive = true;
	philo[i]->time_left_death = data->ttd;
	philo[i]->time_left_eat = data->tte;
	philo[i]->time_left_sleep = data->tts;
	while (forks->fork_id != (int)(i + 1))
		forks = forks->next;
	philo[i]->left_fork = forks;
	if (i > 0)
		philo[i]->right_fork = philo[i - 1]->left_fork;
	philo[i]->initial_time = data->initial_time;
}

void	free_philo(t_philo **philo)
{
	int	i;

	i = -1;
	while (philo[++i])
		free(philo[i]);
	free(philo);
}
