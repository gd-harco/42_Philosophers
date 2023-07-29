/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:57:03 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/29 14:57:07 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks_solo(t_philo *philo);

void	*thread_routine_solo(void *thread_id)
{
	t_philo	*philo;

	philo = (t_philo *)thread_id;
	gettimeofday(&philo->startup_time, NULL);
	philo->time_of_last_meal = philo->startup_time;
	take_forks_solo(philo);
	return (NULL);
}

static int	take_forks_solo(t_philo *philo)
{
	if (check_death(philo) == DEATH)
		return (DEATH);
	print_action(philo, "has taken a fork");
	while (check_death(philo) != DEATH)
		msleep(5, philo);
	return (DEATH);
}
