#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	*main;
	pthread_mutex_t start;

	if (argc != 5 && argc != 6)
		return (write(2, USAGE, sizeof(USAGE)), 1);

	pthread_mutex_lock(&start);
	main = init_main(argc, argv);
	if (!main)
		return (write(2, "init error!\n", 14), 1);
	pthread_mutex_unlock(&start);
	get_start_time(&main->start_time);
	pthread_mutex_lock(&main->print_lock);
	printf("start time: %i\n", main->start_time);
	pthread_mutex_unlock(&main->print_lock);
	sleep(1);
	pthread_mutex_lock(&main->print_lock);
	printf("time passed: %i\n", calc_elapsed(main->start_time));
	pthread_mutex_unlock(&main->print_lock);
	free_all(main);
	return(0);
}

