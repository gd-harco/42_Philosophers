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
 * @brief returns the elapsed time in milliseconds
 * @param initial_time the time to compare to
 * @return an int representing the time difference in milliseconds
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

//TODO: Implement philo death check.
/**
 * @brief Reimplementation of usleep in milliseconds instead of microseconds.\n
 * Does 10 milliseconds sleeps than checks if the philo is still alive. \n
 * Loop until the philo is dead or the sleep time is over.
 * @param sleep_time The time to sleep in milliseconds
 * @param philo The philo concerned by the sleep
 */
void	ft_usleep(int sleep_time, t_philo *philo)
{
	while (sleep_time > 10 && philo->is_alive)
	{
		usleep(10 * 1000);
		sleep_time -= 10;
	}
	if (philo->is_alive)
		usleep(sleep_time * 1000);
}
