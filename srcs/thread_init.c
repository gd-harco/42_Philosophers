
#include "philo.h"

int		create_forks(t_fork **forks, int nb_fork);
t_fork	*new_fork(t_fork *previous, t_fork *first, int id);
int		add_back(t_fork **forks, t_fork *new);
void	fork_free(t_fork **forks);

int	init_philo_fork(t_data *data)
{
	if (create_forks(data->forks, data->nb_of_philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fork_free(data->forks);
}

//TODO: GUILLAUME APPREND A CREER UNE LISTE CHAINE
int	create_forks(t_fork **forks, int nb_fork)
{
	t_fork	*previous;
	t_fork	*current;
	int		i;

	i = 1;
	previous = NULL;
	current = new_fork(previous, NULL, i);
	forks = &current;
	while (++i <= nb_fork)
	{
		current = new_fork(previous, NULL, i);
		if (!current)
			return (fork_free(forks), EXIT_FAILURE);
		add_back(forks, current);
		i++;
	}
	current = new_fork(previous, *forks, i);
	add_back(forks, current);
	return (EXIT_SUCCESS);
}

t_fork	*new_fork(t_fork *previous, t_fork *first, int id)
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

int	add_back(t_fork **forks, t_fork *new)
{
	t_fork	*current;

	if (!forks)
		return (forks = new, EXIT_SUCCESS);
	current = *forks;
	while (current->next)
		current = current->next;
	current->next = new;
	return (EXIT_SUCCESS);
}

void	fork_free(t_fork **forks)
{
	t_fork	*current;
	t_fork	*next;

	current = *forks;
	while (current)
	{
		next = current->next;
		pthread_mutex_destroy(&current->f_mutex);
		free(current);
		current = next;
	}
}
