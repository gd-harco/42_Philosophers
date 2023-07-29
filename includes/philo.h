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
# include <printf.h>
# include <unistd.h>
# include <stdlib.h>
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
	pthread_t		thread;
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
	size_t			nb_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			nb_goal;
	t_mutex_list	mutex_list;
	t_fork			*forks;
	t_philo			**philos;
}					t_data;

//----------- Function -----------//
//########### TIME_C ###########//
t_ms	get_time_since(t_ms initial_time);
t_ms	get_current_time(void);
int		msleep(t_ms ms_to_sleep, t_philo *philo);

//########### PARSING_C ###########//
int		parse_argv(int argc, char **argv, t_data *data);

//########### FREE_DATA_C ###########//
int		exit_free_data(t_data *data);

//########### THREAD_INIT_C ###########//
int		init_philo_fork(t_data *data);
void	philos_free(t_philo **philo);

//########### FORK_UTILS_C ###########//
int		create_forks(t_data *data);
void	fork_free(t_fork *forks);
bool	get_fork_availability(t_fork *fork);

//########### UTILITY_FUNCTIONS ###########//
int		ft_atoi(const char *str);
bool	is_event(int philo_id);

int		init_threads(t_data *data);

//########### THREAD_ROUTINE.C ###########//
void	*thread_routine(void *thread_id);
void	*thread_routine_solo(void *thread_id);

//########### DEATH_HANDLING.C ###########//
void	call_goal_achieve(t_philo *philo);
void	call_death(t_philo *philo);
void	exit_death(t_data *data);
int		check_death(t_philo *philo);

void	print_action(t_philo *philo, char *action);

# define DEATH 666
//----------- Error message -----------//
# define INVALID_ARGC "philo: error: invalid number of arguments\n \
Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat] (optional)\n"
# define INVALID_ARGV "philo: error: invalid char in argument detected\n"
# define ERROR_INITIALISATION "philo: error: initialisation failed\n"

#endif
