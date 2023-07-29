/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:53:23 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/29 14:55:18 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	call_goal_achieve(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	philo->is_alive = false;
	philo->mutex_list->dead_philo_check = true;
	pthread_mutex_unlock(&philo->mutex_list->is_alive_mutex);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}

void	call_death(t_philo *philo)
{
	print_action(philo, "died");
	pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	philo->mutex_list->dead_philo_check = true;
	philo->is_alive = false;
	pthread_mutex_unlock(&philo->mutex_list->is_alive_mutex);
}

void	exit_death(t_data *data)
{
	int	i;

	i = -1;
	while (data->philos[++i])
		pthread_join(data->philos[i]->thread, NULL);
	fork_free(data->forks);
	philos_free(data->philos);
	mutex_list_destroy(&data->mutex_list);
}

int	check_death(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	current_time.tv_sec -= philo->time_of_last_meal.tv_sec;
	current_time.tv_usec -= philo->time_of_last_meal.tv_usec;
	if ((current_time.tv_sec * 1000
			+ current_time.tv_usec / 1000) > philo->time_to_die)
	{
		call_death(philo);
		return (DEATH);
	}
	return (EXIT_SUCCESS);
}
