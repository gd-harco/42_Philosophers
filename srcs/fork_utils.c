#include "philo.h"

static void		add_back(t_fork *previous, t_fork *new, t_fork **list_data);
static t_fork	*new_fork(t_fork *previous, int id);

bool	get_fork_availability(t_fork *fork)
{
	pthread_mutex_lock(&fork->f_mutex);
	if (fork->fork_available)
		return (pthread_mutex_unlock(&fork->f_mutex), true);
	else
		return (pthread_mutex_unlock(&fork->f_mutex), false);
}

int	create_forks(t_data *data)
{
	t_fork	*previous;
	t_fork	*current;
	size_t	i;

	i = 0;
	data->forks = NULL;
	previous = NULL;
	while (++i <= data->nb_of_philo)
	{
		current = new_fork(previous, i);
		if (!current)
			return (EXIT_FAILURE);
		add_back(previous, current, &data->forks);
		previous = current;
	}
	return (EXIT_SUCCESS);
}

static t_fork	*new_fork(t_fork *previous, int id)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->previous = previous;
	fork->fork_id = id;
	fork->fork_available = true;
	if (pthread_mutex_init(&fork->f_mutex, NULL) != 0)
		return (free(fork), NULL);
	fork->next = NULL;
	return (fork);
}

static void	add_back(t_fork *previous, t_fork *new, t_fork **list_data)
{
	if (!previous)
		*list_data = new;
	else
		previous->next = new;
}
