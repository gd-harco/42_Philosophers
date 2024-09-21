/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:55:49 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/29 14:56:45 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_free_data(t_data *data)
{
	pthread_mutex_unlock(&data->mutex_list.sync);
	if (data->philos)
		philos_free(data->philos);
	if (data->forks)
		fork_free(data->forks);
	return (42);
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
	pthread_mutex_destroy(&mutex_list->sync);
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
