#include "philo.h"

int	main(int argc, char **argv)
{
	t_main					*main;
	int						idx;
	int						num_dead;
	int						ms_elapsed;

	if (argc != 5 argc != 6)
		return (write(2, USAGE, sizeof(USAGE)), 1);

	main = init_main(argc, argv);
	if (!main)
		return (write(2, "init error!\n", 14), 1);

	num_dead = 0;
	ms_elapsed = 0;
	while (num_dead == 0)
	{
		ms_elapsed = 






	}
	return(0);
}
