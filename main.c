#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc != 5 && argc != 6)
		return (write(2, USAGE, sizeof(USAGE)), 1);

	main = init_main(argc, argv);
	if (!main)
		return (write(2, "init error!\n", 14), 1);
	printf("philos %i's state is %i\n", main->philos[0]->idx, main->philos[0]->state);
	free_all(main);
	return(0);
}

