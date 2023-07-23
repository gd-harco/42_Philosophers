#include "philo.h"

int	exit_free_data(t_data *data)
{
	if (data->philos)
		free_philo(data->philos);
	if (data->forks)
		fork_free(data->forks);
	return (42);
}
