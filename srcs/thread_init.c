
#include "philo.h"

t_fork	*create_forks(int nb_fork);
t_fork	*new_fork(t_fork *previous, int id);
t_philo	*new_philo(t_philo *previous, int i, t_fork *forks);
void	add_back(t_fork **forks, t_fork *new);
void	fork_free(t_fork *forks);
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
		philo[i]->data = data;
	}
	philo[i] = NULL;
	philo[0]->right_fork = philo[i - 1]->left_fork;
	data->philos = philo;
	return (EXIT_SUCCESS);
}

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

t_fork	*new_fork(t_fork *previous, int id)
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

void	add_back(t_fork **forks, t_fork *new)
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
