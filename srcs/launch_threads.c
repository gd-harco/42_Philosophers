#include "philo.h"

void	*thread_routine(void *thread_id);
int		detach_threads_error(t_philo **philos, int i);

/**
 * @brief Initialise all of the threads. \n
 * If one initialisation failed,detach all previously launch thread.
 * @param data data struct
 * @return EXIT_SUCCESS if all thread launch properly. \n
 * EXIT_FAILURE otherwise
 */
int	init_threads(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->nb_of_philo)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&thread_routine, &data->philos[i]->philo_id) != 0)
			return (detach_threads_error(data->philos, i),
				exit_free_data(data));
	}
	return (EXIT_SUCCESS);
}

void	*thread_routine(void *thread_id)
{
	int	*id;

	id = (int *)thread_id;
	printf ("Hello from thread %d\n", *id);
	return (NULL);
}

/**
 * @brief Detach all thread to exit the program cleanly
 * @param philos The philos array
 * @param i The index number of the failed thread
 * @return EXIT_FAILURE
 */
int	detach_threads_error(t_philo **philos, int i)
{
	while (--i <= 0)
		pthread_detach(philos[i]->thread);
	return (EXIT_FAILURE);
}