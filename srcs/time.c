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
t_ms	get_current_time(void)
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
t_ms	get_time_since(t_ms initial_time)
{
	struct timeval	current_time;
	t_ms 			calculated_time;

	gettimeofday(&current_time, NULL);
	calculated_time = (current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000);
	return (calculated_time - initial_time);
}

/**
 * @brief A re-implementation of usleep(3) in milliseconds.\n
 * Perform multiple 5 milisecond sleeps until the desired time is reached.\n
 * Check if the philosopher is still alive every 5 miliseconds.
 * @param ms_to_sleep The time to sleep in milliseconds.
 * @param philo The philosopher to check for death.
 */
int	msleep(t_ms ms_to_sleep, t_philo *philo)
{
	t_ms	slept;
	t_ms	start_time;

	if (!philo)
		return (usleep(ms_to_sleep * 1000));
	start_time = get_current_time();
	slept = 0;
	while (slept < ms_to_sleep)
	{
		usleep(5 * 1000);
		if (check_death(philo) == DEATH)
			return (DEATH);
		slept = get_time_since(start_time);
	}
	return (EXIT_SUCCESS);
}
