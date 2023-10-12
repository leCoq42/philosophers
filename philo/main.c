#include "philo.h"

static void	print_one_philo(t_main *main);

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc != 5 && argc != 6)
		return (print_usage_error(), 1);
	if (input_check(argc, argv))
		return (ph_putstr_fd("Invalid Input!\n", 1), 1);
	main = init_structs(argc, argv);
	if (!main)
		return (ph_putstr_fd("Init error!\n", 2), free_all(main), 1);
	if (main->config.num_philos == 1)
		print_one_philo(main);
	else
	{
		if (create_threads(main) == 1)
			return (free_all(main), 1);
		observer(main);
	}
	end_program(main);
}

void	print_one_philo(t_main *main)
{
	printf("0 1 has taken a fork\n");
	printf("%u 1 died\n", main->config.time_to_die_ms);
}
