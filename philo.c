#include "philo.h"

/* static void	print_locked(t_philo *philo); */

void	*philo_func(void *arg)
{
	t_philo	*philo;
	int	forks[2];
	
	philo = (t_philo *)arg;
	forks[RIGHT] = philo->idx;
	forks[LEFT] = philo->idx + 1;
	if (forks[LEFT] == philo->main->config->num_philos)
		forks[LEFT] = 0;
	/* write_synced(philo); */
	grab_forks(philo, forks);
	down_forks(philo, forks);
	return (NULL);
}

void	grab_forks(t_philo *philo, int *forks)
{
	pthread_mutex_lock(&philo->main->print_lock);
	printf("philo %d is born!, Right fork: %d, Left fork: %d.\n", philo->idx, forks[RIGHT], forks[LEFT]);
	pthread_mutex_lock(philo->main->forks[forks[RIGHT]]);
	printf("philo %d grabbed his right fork.\n", philo->idx);
	pthread_mutex_lock(philo->main->forks[forks[LEFT]]);
	printf("philo %d grabbed his left fork.\n", philo->idx);
	printf("philo %d is eating\n", philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
}

void	down_forks(t_philo *philo, int *forks)
{
	pthread_mutex_lock(&philo->main->print_lock);
	printf("philo %d put down his right fork.\n", philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
	pthread_mutex_unlock(philo->main->forks[forks[RIGHT]]);
	pthread_mutex_lock(&philo->main->print_lock);
	printf("philo %d put down his left fork.\n", philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
	pthread_mutex_unlock(philo->main->forks[forks[LEFT]]);
}
/**/
/* void	write_synced(t_philo *philo) */
/* { */
/* 	pthread_mutex_lock(&philo->main->print_lock); */
/* 	ft_putstr_fd("philo ", 1); */
/* 	ft_putnbr_fd(philo->idx, 1); */
/* 	ft_putstr_fd(" is born! ", 1); */
/* 	ft_putstr_fd("Right fork: ", 1); */
/* 	ft_putnbr_fd(philo->idx, 1); */
/* 	ft_putstr_fd(", Left fork: ", 1); */
/* 	if (philo->idx + 1 == philo->main->config->num_philos) */
/* 		ft_putnbr_fd(0, 1); */
/* 	else */
/* 		ft_putnbr_fd(philo->idx + 1, 1); */
/* 	ft_putstr_fd("\n", 1); */
/* 	pthread_mutex_unlock(&philo->main->print_lock); */
/* } */


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
