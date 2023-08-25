#include	"philo.h"


int	main(int argc, char **argv)
{
	t_philo	**philo;

	if (argc != 5 argc != 6)
		return (write(2, USAGE, sizeof(USAGE)), 1);
	philo = malloc(sizeof(t_philo *) * (ft_atoi(argv[1])));
		return (write(2, "malloc error!\n", 14), 1);
	memset(philo, 0, sizeof(t_philo *) * (ft_atoi(argv[1])));
	
















	return (0);
}
