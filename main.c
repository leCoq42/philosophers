#include "philo.h"


int	main(int argc, char **argv)
{
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	t_philo					**philo;
	int						idx;
	int						total_threads;

	if (argc != 5 argc != 6)
		return (write(2, USAGE, sizeof(USAGE)), 1);
	total_threads = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo *) * total_threads);
	if (!philo)
		return (write(2, "malloc error!\n", 14), 1);
	memset(philo, 0, sizeof(t_philo *) * total_threads);
	idx = 0;
	while (idx < total_threads)
		philo[idx] = init_philo(idx, philo[idx]);
	

	
	
















	exit (EXIT_SUCCESS);
}
