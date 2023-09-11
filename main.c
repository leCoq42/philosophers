#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	*main;
	/* pthread_mutex_t start; */

	if (argc != 5 && argc != 6)
		return (write(2, USAGE, sizeof(USAGE)), 1);

	/* pthread_mutex_lock(&start); */
	main = init_main(argc, argv);
	if (!main)
		return (write(2, "init error!\n", 14), 1);
	pthread_mutex_lock(&main->print_lock);
	get_start_time(&main->start_time);
	printf("start time:%ld\n", main->start_time);
	pthread_mutex_unlock(&main->print_lock);
	philo_run(main);
	/* pthread_mutex_unlock(&start); */
	/* sleep(1); */
	pthread_mutex_lock(&main->print_lock);
	printf("time passed: %ld\n", calc_elapsed(main->start_time));
	pthread_mutex_unlock(&main->print_lock);
	join_threads(main->philos);
	free_all(main);
	return(0);
}

