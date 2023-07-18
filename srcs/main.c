# include "philo.h"

static int	get_random(int max);
static void	*store_function(void *p_data);
static void	*client_function(void *p_data);

int main(void)
{
	int i = -1;
	int	ret = 0;

	printf("Crteation du thread store\n");
	ret = pthread_create(&store.thread_store, NULL, store_function, NULL);
	if (!ret)
	{
		printf("Creation des thread client\n");
		while (++i < NB_CLIENTS)
		{
			ret = pthread_create(&store.thread_clients[i], NULL,
				client_function, (void *)i);
			if (!ret)
				printf("thread numero %d cree avec succes\n", i);
			else
				dprintf(STDERR_FILENO, "%s", strerror(ret));
		}
	}
	else
		dprintf(STDERR_FILENO, "%s", strerror(ret));
	i = 0;
	while (i < NB_CLIENTS)
		pthread_join(store.thread_clients[i++], NULL);
	pthread_join(store.thread_store, NULL);
}

static int	get_random(int max)
{
	double	val;

	val = (double)max * rand();
	val = val / (RAND_MAX + 1.0);
	return ((int)val);
}

static void	*store_function(void *p_data)
{
	while (true)
	{
		if (store.stock <= 0)
		{
			store.stock = INITIAL_STOCK;
			printf("The store is full again, restocked to %d\n", store.stock);
		}
	}
	return (NULL);
}

static void * client_function (void * p_data)
{
	int nb = (int) p_data;

	while (1)
	{
		int val = get_random (6);

		psleep (get_random (3));

		store.stock = store.stock - val;
		printf (
			"Client %d prend %d du stock, reste %d en stock !\n",
			nb, val, store.stock
		);
	}

	return NULL;
}
