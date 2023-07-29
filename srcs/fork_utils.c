/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:55:41 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/29 14:55:43 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		add_back(t_fork *previous, t_fork *new, t_fork **list_data);
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

int	even_philo_take_forks(t_philo *philo)
{
	if (check_death(philo) == DEATH)
		return (DEATH);
	pthread_mutex_lock(&philo->left_fork->f_mutex);
	print_action(philo, "has taken a fork");
	if (check_death(philo) == DEATH)
	{
		pthread_mutex_unlock(&philo->left_fork->f_mutex);
		return (DEATH);
	}
	pthread_mutex_lock(&philo->right_fork->f_mutex);
	print_action(philo, "has taken a fork");
	if (check_death(philo) == DEATH)
	{
		pthread_mutex_unlock(&philo->left_fork->f_mutex);
		pthread_mutex_unlock(&philo->right_fork->f_mutex);
		return (DEATH);
	}
	return (EXIT_SUCCESS);
}

int	odd_philo_take_forks(t_philo *philo)
{
	if (check_death(philo) == DEATH)
		return (DEATH);
	pthread_mutex_lock(&philo->right_fork->f_mutex);
	print_action(philo, "has taken a fork");
	if (check_death(philo) == DEATH)
	{
		pthread_mutex_unlock(&philo->right_fork->f_mutex);
		return (DEATH);
	}
	pthread_mutex_lock(&philo->left_fork->f_mutex);
	print_action(philo, "has taken a fork");
	if (check_death(philo) == DEATH)
	{
		pthread_mutex_unlock(&philo->left_fork->f_mutex);
		pthread_mutex_unlock(&philo->right_fork->f_mutex);
		return (DEATH);
	}
	return (EXIT_SUCCESS);
}
