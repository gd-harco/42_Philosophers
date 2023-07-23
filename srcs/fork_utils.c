#include "philo.h"

static void		add_back(t_fork **forks, t_fork *new);
static t_fork	*new_fork(t_fork *previous, int id);

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
		add_back(&data->forks, current);
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
	fork->available = true;
	if (pthread_mutex_init(&fork->f_mutex, NULL) != 0)
		return (free(fork), NULL);
	fork->next = NULL;
	return (fork);
}

//TODO : Set new element using previous, avoid iterating on the whole list
static void	add_back(t_fork **forks, t_fork *new)
{
	t_fork	*current;

	if (!forks)
		return ;
	if (*forks)
	{
		current = *forks;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else
		*forks = new;
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
