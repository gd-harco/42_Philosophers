#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <strings.h>
# include <unistd.h>
# include <stdbool.h>
# include <strings.h>
# define psleep(sec) sleep ((sec))
# define INITIAL_STOCK   20
# define NB_CLIENTS      5

/* Structure stockant les informations des threads clients et du magasin. */
typedef struct s_store
{
	int stock;

	pthread_t thread_store;
	pthread_t thread_clients [NB_CLIENTS];
}	t_store;

static t_store store =
{
	.stock = INITIAL_STOCK,
};

#endif
