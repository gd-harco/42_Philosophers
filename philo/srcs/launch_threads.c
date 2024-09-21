/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:56:52 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/29 14:56:54 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	detach_threads_error(t_philo **philos, int i);

/**
 * @brief Initialise all of the threads. \n
 * If one initialisation failed,detach all previously launch thread.
 * @param data data struct
 * @return EXIT_SUCCESS if all thread launch properly. \n
 * EXIT_FAILURE otherwise
 */
int	init_threads(t_data *data)
{
	long	i;

	if (data->nb_of_philo == 1)
	{
		if (pthread_create(&data->philos[0]->thread, NULL,
				&thread_routine_solo, data->philos[0]) != 0)
			return (detach_threads_error(data->philos, 0),
				exit_free_data(data));
		return (EXIT_SUCCESS);
	}
	i = -1;
	pthread_mutex_lock(&data->mutex_list.sync);
	while (++i < data->nb_of_philo)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&thread_routine, data->philos[i]) != 0)
			return (detach_threads_error(data->philos, i),
				exit_free_data(data));
	}
	pthread_mutex_unlock(&data->mutex_list.sync);
	return (EXIT_SUCCESS);
}

/**
 * @brief Detach all thread to exit the program cleanly
 * @param philos The philos array
 * @param i The index number of the failed thread
 * @return EXIT_FAILURE
 */
static int	detach_threads_error(t_philo **philos, int i)
{
	while (--i <= 0)
		pthread_detach(philos[i]->thread);
	return (EXIT_FAILURE);
}
