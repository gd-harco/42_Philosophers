/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:43:07 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/21 14:43:08 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//########### SYSTEM LIB HEADERS ##########//
# include <pthread.h>
# include <sys/time.h>
# include <malloc.h>
# include <printf.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

//----------- Struct -----------//
typedef struct s_fork	t_fork;

struct s_fork
{
	t_fork			*previous;
	int				fork_id;
	bool			available;
	pthread_mutex_t	f_mutex;
	t_fork			*next;
};

typedef struct s_philo
{
	int			philo_id;
	bool		is_alive;
	pthread_t	thread;
	size_t		time_left_death;
	size_t		time_left_eat;
	size_t		time_left_think;
	size_t		time_left_sleep;
	t_fork		*left_fork;
	t_fork		*right_fork;
}			t_philo;

typedef struct s_data
{
	size_t	nb_of_philo;
	size_t	ttd;
	size_t	tte;
	size_t	tts;
	size_t	nb_goal;
	t_fork	*forks;
	t_philo	**philos;
}				t_data;

//----------- Function -----------//
//########### TIME_C ###########//
int		get_elapsed_time(struct timeval *initial_time);

//########### PARSING_C ###########//
void	parse_argv(int argc, char **argv, t_data *data);

//########### THREAD_INIT_C ###########//
void	init_philo_fork(t_data *data);

//########### FORK_UTILS_C ###########//
t_fork	*create_forks(int nb_fork);

//########### UTILITY_FUNCTIONS ###########//
int		ft_atoi(const char *str);

//----------- Error message -----------//
# define INVALID_ARGC "philo: error: invalid number of arguments\n \
Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat] (optional)\n"
# define INVALID_ARGV "philo: error: invalid char in argument detected\n"
#endif
