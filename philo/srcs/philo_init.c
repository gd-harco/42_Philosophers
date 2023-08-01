/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:56:58 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/29 14:56:59 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philos(t_data *data);
static void	create_one_philo(t_philo **philo, t_data *data, int i);

int	init_philo_fork(t_data *data)
{
	if (create_forks(data) == EXIT_FAILURE
		|| create_philos(data) == EXIT_FAILURE)
		return (exit_free_data(data));
	return (EXIT_SUCCESS);
}

static int	create_philos(t_data *data)
{
	t_philo	**philo;
	size_t	i;

	philo = malloc(sizeof(t_philo *) * (data->nb_of_philo + 1));
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
	if (data->nb_of_philo == 1)
		philo[0]->right_fork = NULL;
	else
		philo[0]->right_fork = philo[i - 1]->left_fork;
	return (EXIT_SUCCESS);
}

static void	create_one_philo(t_philo **philo, t_data *data, int i)
{
	t_fork	*forks;

	forks = data->forks;
	philo[i]->eat_count = 0;
	if (data->philo_eat_goal)
		philo[i]->eat_goal = data->nb_goal;
	else
		philo[i]->eat_goal = -1;
	pthread_mutex_init(&philo[i]->time_of_last_meal_mutex, NULL);
	pthread_mutex_init(&philo[i]->is_satiated_mutex, NULL);
	philo[i]->philo_id = i + 1;
	philo[i]->is_alive = true;
	philo[i]->is_satiated = false;
	philo[i]->time_to_die = data->time_to_die;
	philo[i]->time_to_eat = data->time_to_eat;
	philo[i]->time_to_sleep = data->time_to_sleep;
	while (forks->fork_id != i + 1)
		forks = forks->next;
	philo[i]->left_fork = forks;
	if (i > 0)
		philo[i]->right_fork = philo[i - 1]->left_fork;
	philo[i]->mutex_list = &data->mutex_list;
}
