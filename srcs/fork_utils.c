#include "philo.h"

static void		add_back(t_fork **forks, t_fork *new);
static t_fork	*new_fork(t_fork *previous, int id);
static void		fork_free(t_fork *forks);

t_fork	*create_forks(int nb_fork)
{
	t_fork	*forks_list;
	t_fork	*previous;
	t_fork	*current;
	int		i;

	i = 0;
	forks_list = NULL;
	previous = NULL;
	while (++i <= nb_fork)
	{
		current = new_fork(previous, i);
		if (!current)
			return (fork_free(forks_list), NULL);
		add_back(&forks_list, current);
		previous = current;
	}
	return (forks_list);
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

static void	fork_free(t_fork *forks)
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
