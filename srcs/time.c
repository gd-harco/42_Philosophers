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
 * @brief get the current time in milliseconds
 * This is just a wrapper for gettimeofday that returns the time in milliseconds
 * @return an int representing the current time in milliseconds
 */
int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @brief Returns the elapsed time in milliseconds.
 * @param initial_time The time to compare to.
 * @return An int representing the time difference in milliseconds.
 */
int	get_time_since(int initial_time)
{
	struct timeval	current_time;
	int				calculated_time;

	gettimeofday(&current_time, NULL);
	calculated_time = (current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000);
	return (calculated_time - initial_time);
}

/**
 * @brief A re-implementation of usleep(3) in mil
 * @param ms_to_sleep
 * @param philo
 */
void msleep(int ms_to_sleep, t_philo *philo)
{
	if (!philo)
		return (usleep(ms_to_sleep * 1000), (void)0);
	while (ms_to_sleep >= 5)
	{
		usleep(5 * 1000);
		ms_to_sleep -=5;
		check_death(philo);
	}
	if (ms_to_sleep != 0)
	{
		usleep(ms_to_sleep * 1000);
		check_death(philo);
	}
}
