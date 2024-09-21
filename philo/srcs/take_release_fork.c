/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:57:11 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/29 14:57:12 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_left_fork(t_philo *philo)
{
	bool	left_fork;

	left_fork = false;
	while (!left_fork)
	{
		pthread_mutex_lock(&philo->left_fork->f_mutex);
		if (philo->left_fork->fork_available)
		{
			left_fork = true;
			philo->left_fork->fork_available = false;
			print_action(philo, YELLOW"has taken a fork");
			pthread_mutex_unlock(&philo->left_fork->f_mutex);
		}
		else
		{
			pthread_mutex_unlock(&philo->left_fork->f_mutex);
			usleep(1);
		}
	}
}

void	take_right_fork(t_philo *philo)
{
	bool	right_fork;

	right_fork = false;
	while (!right_fork)
	{
		pthread_mutex_lock(&philo->right_fork->f_mutex);
		if (philo->right_fork->fork_available)
		{
			right_fork = true;
			philo->right_fork->fork_available = false;
			print_action(philo, YELLOW"has taken a fork");
			pthread_mutex_unlock(&philo->right_fork->f_mutex);
		}
		else
		{
			pthread_mutex_unlock(&philo->right_fork->f_mutex);
			usleep(1);
		}
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->f_mutex);
	philo->left_fork->fork_available = true;
	pthread_mutex_unlock(&philo->left_fork->f_mutex);
	pthread_mutex_lock(&philo->right_fork->f_mutex);
	philo->right_fork->fork_available = true;
	pthread_mutex_unlock(&philo->right_fork->f_mutex);
	print_action(philo, YELLOW"has released the forks");
}
