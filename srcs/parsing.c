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

bool	check_minus(int argc, char **argv);
bool	invalid_char(int argc, char **argv);
int		init_mutex_list(t_data *data);

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
	if (argc < 5 || argc > 6)
		return (printf(INVALID_ARGC), EXIT_FAILURE);
	if (invalid_char(argc, argv))
		return (printf(INVALID_ARGV), EXIT_FAILURE);
	if (argc == 6)
	{
		data->philo_eat_goal = true;
		data->nb_goal = ft_atoi(argv[5]);
	}
	else
	{
		data->philo_eat_goal = false;
		data->nb_goal = -1;
	}
	init_mutex_list(data);
	data->nb_of_philo = ft_atoi(argv[1]);
	data->philo_dead = false;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->forks = NULL;
	data->philos = NULL;
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
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

int	init_mutex_list(t_data *data)
{
	data->mutex_list.dead_philo_check = false;
	pthread_mutex_init(&data->mutex_list.print_mutex, NULL);
	pthread_mutex_init(&data->mutex_list.is_alive_mutex, NULL);
	pthread_mutex_init(&data->mutex_list.sync, NULL);
	return (EXIT_SUCCESS);
}
