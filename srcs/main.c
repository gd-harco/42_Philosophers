# include "philo.h"

static int	get_elapsed_time(struct timeval *initial_time);


int main(void)
{
	struct timeval	initial_time;
	int				elapsed_time;
	int				i;

	gettimeofday(&initial_time, NULL);
	while (true)
	{
		elapsed_time = get_elapsed_time(&initial_time);
		printf("Time elapsed since program start: %d\n", elapsed_time);
		usleep(1000000);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief returns the elapsed time in milliseconds
 * @param initial_time a pointer to a timeval struct r
 * epresenting the initial time, * set at the beginning of the program
 * @return an int representing the elapsed time in milliseconds
 */
inline int	get_elapsed_time(struct timeval *initial_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - initial_time->tv_sec) * 1000
		+ (current_time.tv_usec - initial_time->tv_usec) / 1000);
}
