/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:43:12 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/21 14:43:13 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitoring(t_data *data);
static int	check_satieted(size_t i, t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf(INVALID_ARGC), EXIT_FAILURE);
	if (check_null(argc, argv))
		return (printf(NULL_ARGV), EXIT_FAILURE);
	if (invalid_char(argc, argv))
		return (printf(INVALID_ARGV), EXIT_FAILURE);
	if (parse_argv(argc, argv, &data) == EXIT_FAILURE
		|| init_philo_fork(&data) == EXIT_FAILURE
		|| init_threads(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	msleep(data.time_to_die / 2);
	return (monitoring(&data));
}

int	monitoring(t_data *data)
{
	long	i;

	while (true)
	{
		data->philo_satieted = 0;
		i = -1;
		while (++i < data->nb_of_philo && check_death(data->philos[i]) != DEATH)
		{
			if (data->philo_eat_goal && check_satieted(i, data) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
		}
		pthread_mutex_lock(&data->mutex_list.is_alive_mutex);
		if (data->mutex_list.dead_philo_check)
		{
			pthread_mutex_unlock(&data->mutex_list.is_alive_mutex);
			exit_death(data);
			return (EXIT_SUCCESS);
		}
		pthread_mutex_unlock(&data->mutex_list.is_alive_mutex);
	}
}

static int	check_satieted(size_t i, t_data *data)
{
	pthread_mutex_lock(&data->philos[i]->is_satiated_mutex);
	if (data->philos[i]->is_satiated)
		data->philo_satieted++;
	pthread_mutex_unlock(&data->philos[i]->is_satiated_mutex);
	if (data->philo_satieted == data->nb_of_philo)
	{
		pthread_mutex_lock(&data->mutex_list.is_alive_mutex);
		data->mutex_list.dead_philo_check = true;
		pthread_mutex_unlock(&data->mutex_list.is_alive_mutex);
		exit_death(data);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
