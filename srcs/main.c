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
	int		i;

	if (parse_argv(argc, argv, &data) == EXIT_FAILURE
		|| init_philo_fork(&data) == EXIT_FAILURE
		|| init_threads(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (!data.philo_dead)
	{
		i = 0;
		while (data.philos[i])
		{
			if (!data.philos[i]->is_alive)
			{
				data.philo_dead = true;
				break ;
			}
			i++;
		}
	}
	exit_death(&data);
	return (EXIT_SUCCESS);
}
