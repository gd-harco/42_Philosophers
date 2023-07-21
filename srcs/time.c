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

/**
 * @brief returns the elapsed time in milliseconds
 * @param initial_time a pointer to a timeval struct r
 * epresenting the initial time, * set at the beginning of the program
 * @return an int representing the elapsed time in milliseconds
 */
int	get_elapsed_time(struct timeval *initial_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - initial_time->tv_sec) * 1000
		+ (current_time.tv_usec - initial_time->tv_usec) / 1000);
}
