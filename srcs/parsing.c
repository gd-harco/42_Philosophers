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
bool	invalid_char(int argc, char **str);

/**
 * @brief Parse argv and store it in data. Set nb_goal to 0 if not specified.
 * Does not check for invalid input. exit if negative number.
 * Set philo and fork struct to NULL.
 * @param argc argument count
 * @param argv argument array
 * @param data pointer to data struct
 */
void	parse_argv(int argc, char **argv, t_data *data)
{
	if (invalid_char(argc, argv))
	{
		printf(INVALID_ARGV);
		exit(EXIT_FAILURE);
	}
	if (argc == 6)
		data->nb_goal = ft_atoi(argv[5]);
	else
		data->nb_goal = 0;
	data->nb_of_philo = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	data->forks = NULL;
	data->philos = NULL;
}

bool	invalid_char(int argc, char **str)
{
	int	i;
	int	j;

	i = 1;
	while (i <= argc)
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] < '0' || '9' < str[i][j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}
