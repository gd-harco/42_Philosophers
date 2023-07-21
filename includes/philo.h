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

struct s_fork
{
	t_fork			*previous;
	bool			available;
	pthread_mutex_t	f_mutex;
	t_fork			*next;
};

#endif
