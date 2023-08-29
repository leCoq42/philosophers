#inclide "philo.h"

t_philo	*init_philo(int idx, t_philo **philo)
{
	t_philo	*philo;
	int		s;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	s = pthread_create(&thread[idx]->tid, NULL, philo_func, &idx)
	if (!s)
		exit(EXIT_FAILURE)
	philo->state = SLEEPING;
	philo->sleep_time = 0;
	return (philo);
}
