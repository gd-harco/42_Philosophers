#include "philo.h"

int	exit_free_data(t_data *data)
{
	if (data->philos)
		philos_free(data->philos);
	if (data->forks)
		fork_free(data->forks);
	return (42);
}
