/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:43:22 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/21 14:43:25 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_initial_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @brief returns the elapsed time in milliseconds
 * @param initial_time Int value storing the startup time,\n
 *	set at the beginning of the program
 * @return an int representing the elapsed time in milliseconds
 */
int	get_elapsed_time(int initial_time)
{
	struct timeval	current_time;
	int				calculated_time;

	gettimeofday(&current_time, NULL);
	calculated_time = (current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000);
	return (calculated_time - initial_time);
}
