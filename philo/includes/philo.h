/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:43:07 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/29 14:55:37 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//########### SYSTEM LIB HEADERS ##########//
# include <pthread.h>
# include <sys/time.h>
# include <malloc.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>

typedef long long int	t_ms;
//----------- Struct -----------//
typedef struct s_fork	t_fork;

struct s_fork
{
	t_fork			*previous;
	int				fork_id;
	bool			fork_available;
	pthread_mutex_t	f_mutex;
	t_fork			*next;
};

typedef struct s_mutex_list
{
	bool			dead_philo_check;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	is_alive_mutex;
	pthread_mutex_t	sync;
}	t_mutex_list;

typedef struct s_philo
{
	int				philo_id;
	bool			is_alive;
	bool			is_satiated;
	pthread_t		thread;
	pthread_mutex_t	time_of_last_meal_mutex;
	pthread_mutex_t	is_satiated_mutex;
	t_mutex_list	*mutex_list;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_to_sleep;
	suseconds_t		time_since_eat;
	struct timeval	time_of_last_meal;
	struct timeval	startup_time;
	int				eat_goal;
	int				eat_count;
	t_fork			*left_fork;
	t_fork			*right_fork;
}				t_philo;

typedef struct s_data
{
	bool			philo_dead;
	bool			philo_eat_goal;
	long			nb_of_philo;
	long			philo_satieted;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_goal;
	t_mutex_list	mutex_list;
	t_fork			*forks;
	t_philo			**philos;
}					t_data;

//----------- Function -----------//
//########### DEATH_HANDLING.C ###########//
void	call_goal_achieve(t_philo *philo);
void	call_death(t_philo *philo);
void	exit_death(t_data *data);
int		check_death(t_philo *philo);

//########### FORK_UTILS_C ###########//
int		create_forks(t_data *data);
void	odd_philo_take_forks(t_philo *philo);
void	even_philo_take_forks(t_philo *philo);

//########### FREE_UTILS_C ###########//
int		exit_free_data(t_data *data);
void	mutex_list_destroy(t_mutex_list *mutex_list);
void	fork_free(t_fork *forks);
void	philos_free(t_philo **philo);

//########### GLOBAL_UTILS_C ###########//
long	ft_atol(const char *str);
int		init_threads(t_data *data);

//########### LAUNCH_THREADS_C ###########//
int		init_threads(t_data *data);

//########### PARSING_C ###########//
int		parse_argv(int argc, char **argv, t_data *data);
bool	invalid_char(int argc, char **argv);
bool	check_null(int argc, char **argv);

//########### PHILO_INIT_C ###########//
int		init_philo_fork(t_data *data);

//########## SOLO_PHILO_C ###########//
void	*thread_routine_solo(void *thread_id);

//########### THREAD_ROUTINE.C ###########//
void	*thread_routine(void *thread_id);
void	print_action(t_philo *philo, char *action);

//########### TIME_C ###########//
void	msleep(t_ms ms_to_sleep);
int		compare_timeval(struct timeval *t1, struct timeval *t2);
void	add_ms_tv(struct timeval *tv, long milliseconds);

//########### TAKE_RELEASE_FORK.C ###########//
void	take_left_fork(t_philo *philo);
void	take_right_fork(t_philo *philo);
void	release_left_fork(t_philo *philo);
void	release_right_fork(t_philo *philo);
void	release_forks(t_philo *philo);

//----------- Print color -----------//
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define RESET "\001\e[m\002"

# define DEATH 666
//----------- Error message -----------//
# define INVALID_ARGC "philo: error: invalid number of arguments\n \
Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat] (optional)\n"
# define INVALID_ARGV "philo: error: invalid char in argument detected\n"
# define NULL_ARGV "philo: error: null argument detected\n"
# define NULL_DURATION "philo: error: duration of 0 or below is invalid\n"
# define NO_PHILO "philo: error: no philosopher to simulate\n"
# define NULL_GOAL "philo: error: an eat goal of 0 is invalid\n"
#endif
