#include "philo.h"

void	*print_locked(t_philo *philo);

void	*philo_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_locked(philo);
	return (NULL);
}

void	*print_locked(t_philo *philo)
{
	pthread_mutex_lock(philo->main->print);
	write(1, "philo ", 6);
	ft_putnbr_fd(philo->idx, 1);
	write(1, " is born!\n", 10);
	pthread_mutex_unlock(philo->main->print);
	return (NULL);
}


/* int	check_forks(int idx, t_main **main) */
/* { */
/* 	if (idx == 0) */
/* 	{ */
/* 		if (forks[num_philos - 1]->state == FREE && forks[idx]->state == FREE) */
/* 			return (1); */
/* 	} */
/* 	else if (idx == main->num_philos - 1) */
/* 	{ */
/* 		if (forks[idx] == FREE && forks[0] == FREE) */
/* 			return (1); */
/* 	} */
/* 	else */
/* 	{ */
/* 		if (forks[idx] == FREE && forks[idx + 1] == FREE) */
/* 			return (1); */
/* 	} */
/* 	return (0); */
/* } */
