#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc != 5 && argc != 6)
		error_exit(USAGE, 2);
	main = init_main(argc, argv);
	if (!main)
		error_exit("init error!\n", 2);
	philo_run(main);
	observer(main);
	free_all(main);
	return(0);
}

int8_t	observer(t_main *main)
{
	size_t	idx;

	idx = 0;
	while (1)
	{
		pthread_mutex_lock(&main->obs_lock);
		if (main->philos_done >= main->config.num_philos || main->philos[idx].state == DEAD)
		{
			pthread_mutex_unlock(&main->obs_lock);
			break ;
		}
		pthread_mutex_unlock(&main->obs_lock);
		idx++;
		pthread_mutex_lock(&main->obs_lock);
		if (idx == main->config.num_philos)
			idx = 0;
		pthread_mutex_unlock(&main->obs_lock);
	}
	return (0);
}
