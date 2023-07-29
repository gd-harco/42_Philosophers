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

int	main(int argc, char **argv)
{
	t_data	data;
	size_t	i;

	if (parse_argv(argc, argv, &data) == EXIT_FAILURE
		|| init_philo_fork(&data) == EXIT_FAILURE
		|| init_threads(&data) == EXIT_FAILURE)
		return (printf (ERROR_INITIALISATION), EXIT_FAILURE);
	msleep(data.time_to_die / 2, NULL);
	while (true)
	{
		i = -1;
		while (++i < data.nb_of_philo)
		{
			if (check_death(data.philos[i]) == DEATH)
				break ;
		}
		pthread_mutex_lock(&data.mutex_list.is_alive_mutex);
		if (data.mutex_list.dead_philo_check)
		{
			pthread_mutex_unlock(&data.mutex_list.is_alive_mutex);
			break ;
		}
		pthread_mutex_unlock(&data.mutex_list.is_alive_mutex);
	}
	exit_death(&data);
	return (EXIT_SUCCESS);
}
