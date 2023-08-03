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

static void	philo_eat(t_philo *philo);
static void	philo_sleep(t_philo *philo);
static void	take_forks(t_philo *philo);

void	*thread_routine(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	pthread_mutex_lock(&philo->mutex_list->sync);
	pthread_mutex_unlock(&philo->mutex_list->sync);
	gettimeofday(&philo->startup_time, NULL);
	pthread_mutex_lock(&philo->time_of_last_meal_mutex);
	philo->time_of_last_meal = philo->startup_time;
	pthread_mutex_unlock(&philo->time_of_last_meal_mutex);
	if (philo->philo_id % 2 == 1)
	{
		print_action(philo, BLUE"is thinking");
		usleep(10);
	}
	pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	while (philo->mutex_list->dead_philo_check == false)
	{
		pthread_mutex_unlock(&philo->mutex_list->is_alive_mutex);
		philo_eat(philo);
		philo_sleep(philo);
		usleep(500);
		pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	}
	pthread_mutex_unlock(&philo->mutex_list->is_alive_mutex);
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	print_action(philo, GREEN"is eating");
	pthread_mutex_lock(&philo->time_of_last_meal_mutex);
	gettimeofday(&philo->time_of_last_meal, NULL);
	pthread_mutex_unlock(&philo->time_of_last_meal_mutex);
	msleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->right_fork->f_mutex);
	pthread_mutex_unlock(&philo->left_fork->f_mutex);
	if (philo->eat_goal > 0)
	{
		philo->eat_count++;
		if (philo->eat_count == philo->eat_goal)
		{
			pthread_mutex_lock(&philo->is_satiated_mutex);
			philo->is_satiated = true;
			pthread_mutex_unlock(&philo->is_satiated_mutex);
		}
	}
	return ;
}

static void	philo_sleep(t_philo *philo)
{
	print_action(philo, CYAN"is sleeping");
	msleep(philo->time_to_sleep);
	print_action(philo, BLUE"is thinking");
}

static void	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2)
		even_philo_take_forks(philo);
	else
		odd_philo_take_forks(philo);
}

void	print_action(t_philo *philo, char *action)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->mutex_list->print_mutex);
	pthread_mutex_lock(&philo->mutex_list->is_alive_mutex);
	gettimeofday(&time, NULL);
	time.tv_sec -= philo->startup_time.tv_sec;
	time.tv_usec -= philo->startup_time.tv_usec;
	if (!philo->mutex_list->dead_philo_check)
		printf("%ld\t%d %s\n"RESET, (time.tv_sec * 1000
				+ time.tv_usec / 1000), philo->philo_id, action);
	pthread_mutex_unlock(&philo->mutex_list->is_alive_mutex);
	pthread_mutex_unlock(&philo->mutex_list->print_mutex);
}
