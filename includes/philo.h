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

//----------- Struct -----------//

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_fork
{
	t_fork			*previous;
	int				fork_id;
	bool			available;
	pthread_mutex_t	f_mutex;
	t_fork			*next;
};

struct s_philo
{
	int		philo_id;
	bool	is_alive;
	size_t	time_until_death;
	size_t	time_since_eat_start;
	size_t	time_since_think_start;
	size_t	time_since_sleep_start;
	t_fork	*right_fork;
	t_fork	*left_fork;
	t_data	*data;
};

struct s_data
{
	size_t	nb_of_philo;
	size_t	ttd;
	size_t	tts;
	size_t	tte;
	size_t	nb_goal;
	t_fork	*forks;
	t_philo	*philos;
};

#endif
