
#include "philo.h"

t_philo	*new_philo(t_philo *previous, int i, t_fork *forks);

int	create_philo(t_data *data);

void	init_philo_fork(t_data *data)
{
	data->forks = create_forks(data->nb_of_philo);
	create_philo(data);
}

int	create_philo(t_data *data)
{
	t_philo	**philo;
	size_t	i;

	philo = malloc(sizeof(t_philo *) * data->nb_of_philo + 1);
	if (!philo)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < data->nb_of_philo)
	{
		philo[i + 1] = NULL;
		philo[i] = malloc(sizeof(t_philo));
//		if (!philo[i])
//			return (free_philo(philo), EXIT_FAILURE);
		philo[i]->philo_id = i + 1;
		philo[i]->is_alive = true;
		philo[i]->time_until_death = 0;
		philo[i]->time_since_eat_start = 0;
		philo[i]->time_since_think_start = 0;
		philo[i]->time_since_sleep_start = 0;
		while (data->forks->fork_id != (int)(i + 1))
			data->forks = data->forks->next;
		philo[i]->left_fork = data->forks;
		if (i > 0)
			philo[i]->right_fork = philo[i - 1]->left_fork;
	}
	philo[i] = NULL;
	philo[0]->right_fork = philo[i - 1]->left_fork;
	data->philos = philo;
	return (EXIT_SUCCESS);
}
