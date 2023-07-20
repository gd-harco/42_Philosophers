# include "philo.h"


inline	ssize_t	get_time(ssize_t startup_time)
{
	struct timeval	time;
	ssize_t			res;

	gettimeofday(&time, NULL);
	res = time.tv_sec;
	res *= 1
}

int main(void)
{
	struct timeval	time;
	int				i;

	while (i < 5)
	{
		gettimeofday(&time, NULL);
		printf("current time in sec: %zu\n", time.tv_sec);
		printf("current time in usec: %zu\n", time.tv_usec);
		sleep(5);
		i++;
	}
	return (EXIT_SUCCESS);
}
