/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:43:17 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/21 14:43:21 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex_list(t_data *data);

/**
 * @brief Parse argv and store it in data. Set nb_goal to 0 if not specified.\n
 * If invalid number, return 1.\n
 * Set philo and fork struct to NULL.\n
 * Fill the initial time to the launch time.
 * @param argc argument count
 * @param argv argument array
 * @param data pointer to data struct
 */
int	parse_argv(int argc, char **argv, t_data *data)
{
	memset(data, 0, sizeof(t_data));
	if (argc == 6)
	{
		data->philo_eat_goal = true;
		data->nb_goal = ft_atol(argv[5]);
		if (data->nb_goal == 0)
			return (printf(NULL_GOAL), EXIT_FAILURE);
	}
	else
		data->nb_goal = -1;
	data->nb_of_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->nb_of_philo <= 0)
		return (printf(NO_PHILO), EXIT_FAILURE);
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (printf(NULL_DURATION), EXIT_FAILURE);
	init_mutex_list(data);
	return (EXIT_SUCCESS);
}

/**
 * @brief Check argv to see if the user input is valid.\n
 * When an invalid char is detected, stop and doesn't check the remaining.
 * @param argc
 * @param argv
 * @return true if one invalid character is detected, false otherwise.
 */
bool	invalid_char(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || '9' < argv[i][j])
				if (argv[i][j] != '-')
					return (true);
			j++;
		}
		i++;
	}
	return (false);
}

static int	init_mutex_list(t_data *data)
{
	data->mutex_list.dead_philo_check = false;
	pthread_mutex_init(&data->mutex_list.print_mutex, NULL);
	pthread_mutex_init(&data->mutex_list.is_alive_mutex, NULL);
	pthread_mutex_init(&data->mutex_list.sync, NULL);
	return (EXIT_SUCCESS);
}

bool	check_null(int argc, char **argv)
{
	int i;

	i = 1;
while (i < argc)
	{
		if (!argv[i][0])
			return (true);
		i++;
	}
	return (false);
}
