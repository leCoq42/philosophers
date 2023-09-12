#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	*main;
	/* pthread_mutex_t start; */

	if (argc != 5 && argc != 6)
		error_exit(USAGE, 2);

	/* pthread_mutex_lock(&start); */
	main = init_main(argc, argv);
	if (!main)
		error_exit("init error!\n", 2);
	get_start_time(&main->start_time);
	pthread_mutex_lock(&main->print_lock);
	printf("start time:%ld\n", main->start_time);
	pthread_mutex_unlock(&main->print_lock);
	philo_run(main);
	observer(main);
	/* pthread_mutex_unlock(&start); */
	join_threads(main->philos);
	free_all(main);
	return(0);
}

int8_t	observer(t_main *main)
{
	size_t	idx;

	idx = 0;
	while (main->philos_done < main->config.num_philos)
	{
		if (main->philos[idx].state == 3)
			break ;
		idx++;
		if (idx == main->config.num_philos)
			idx = 0;
	}
	return (0);
}
