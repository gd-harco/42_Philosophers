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

typedef struct s_mutex_list
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	is_alive_mutex;
}	t_mutex_list;

typedef struct s_philo
{
	int				philo_id;
	bool			is_alive;
	pthread_t		thread;
	t_mutex_list	*mutex_list;
	int				time_left_death;
	int				time_left_eat;
	int				time_left_sleep;
	int				loop_left;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				initial_time;
}				t_philo;

typedef struct s_data
{
	size_t			nb_of_philo;
	size_t			ttd;
	size_t			tte;
	size_t			tts;
	size_t			nb_goal;
	t_mutex_list	mutex_list;
	t_fork			*forks;
	t_philo			**philos;
	int				initial_time;
}					t_data;

//----------- Function -----------//
//########### TIME_C ###########//
int		get_elapsed_time(int initial_time);
int		get_initial_time(void);

//########### PARSING_C ###########//
int		parse_argv(int argc, char **argv, t_data *data);

//########### FREE_DATA_C ###########//
int		exit_free_data(t_data *data);

//########### THREAD_INIT_C ###########//
int		init_philo_fork(t_data *data);
void	free_philo(t_philo **philo);

//########### FORK_UTILS_C ###########//
int		create_forks(t_data *data);
void	fork_free(t_fork *forks);

//########### UTILITY_FUNCTIONS ###########//
int		ft_atoi(const char *str);
bool	is_event(int philo_id);

int		init_threads(t_data *data);

//########### THREAD_ROUTINE.C ###########//
void	*thread_routine(void *thread_id);

//----------- Error message -----------//
# define INVALID_ARGC "philo: error: invalid number of arguments\n \
Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat] (optional)\n"
# define INVALID_ARGV "philo: error: invalid char in argument detected\n"
#endif
