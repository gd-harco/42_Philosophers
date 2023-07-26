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
uint64_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((uint64_t)time.tv_sec * (uint64_t)1000 + (uint64_t)time.tv_usec / (uint64_t)1000);
}

/**
 * @brief returns the elapsed time in milliseconds
 * @param initial_time the time to compare to
 * @return an int representing the time difference in milliseconds
 */
uint64_t	get_time_since(uint64_t initial_time)
{
	struct timeval	current_time;
	uint64_t		calculated_time;

	gettimeofday(&current_time, NULL);
	calculated_time = ((uint64_t)current_time.tv_sec * (uint64_t)1000)
		+ ((uint64_t)current_time.tv_usec / (uint64_t)1000);
	return (calculated_time - initial_time);
}

#define SLEEP_TIME 10

/**
 * @brief Reimplementation of usleep in milliseconds instead of microseconds.\n
 * Does 10 milliseconds sleeps than checks if the philo is still alive. \n
 * Loop until the philo is dead or the sleep time is over.
 * @param sleep_time The time to sleep in milliseconds
 * @param philo The philo concerned by the sleep
 */
void ft_usleep(uint64_t ms_to_sleep, t_philo *philo, int *time_since_eat)
{
	uint64_t	us_to_sleep = ms_to_sleep * 1000;

	(void)time_since_eat;
	while (us_to_sleep > 0 && philo->is_alive)
	{
		usleep(SLEEP_TIME);\
		us_to_sleep -= SLEEP_TIME;
	}
}
