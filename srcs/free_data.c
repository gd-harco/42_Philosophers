#include "philo.h"

int	exit_free_data(t_data *data)
{
	pthread_mutex_unlock(&data->mutex_list.sync);
	if (data->philos)
		philos_free(data->philos);
	if (data->forks)
		fork_free(data->forks);
	return (42);
}
