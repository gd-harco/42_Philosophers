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

int	compare_timeval(struct timeval *t1, struct timeval *t2)
{
	if (t1->tv_sec < t2->tv_sec)
		return (-1);
	if (t1->tv_sec > t2->tv_sec)
		return (1);
	if (t1->tv_usec < t2->tv_usec)
		return (-1);
	if (t1->tv_usec > t2->tv_usec)
		return (1);
	return (0);
}

void	add_ms_tv(struct timeval *tv, long milliseconds)
{
	tv->tv_sec += milliseconds / 1000;
	milliseconds %= 1000;
	tv->tv_usec += milliseconds * 1000;
	if (tv->tv_usec >= 1000000)
	{
		tv->tv_sec += tv->tv_usec / 1000000;
		tv->tv_usec %= 1000000;
	}
}

void	msleep(t_ms ms_to_sleep)
{
	struct timeval	goal_time;
	struct timeval	current_time;

	gettimeofday(&goal_time, NULL);
	add_ms_tv(&goal_time, ms_to_sleep);
	gettimeofday(&current_time, NULL);
	while (compare_timeval(&current_time, &goal_time) < 0)
	{
		usleep(1000);
		gettimeofday(&current_time, NULL);
	}
}
