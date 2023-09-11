#include "philo.h"
#include <limits.h>

/* static void	print_locked(t_philo *philo); */
static void	eating(t_philo *philo);
static void	sleeping(t_philo *philo);

int	philo_run(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->config.num_philos)
	{
		if (pthread_create(&main->philos[i].tid, NULL, philo_func, &main->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	*philo_func(void *arg)
{
	t_philo		*philo;
	int			forks[2];
	long long	i;
	long long	goal;

	philo = (t_philo *)arg;
	forks[RIGHT] = philo->idx;
	forks[LEFT] = philo->idx + 1;
	if (forks[LEFT] == philo->main->config.num_philos)
		forks[LEFT] = 0;
	/* pthread_mutex_lock(&philo->main->print_lock); */
	/* printf("philo %d is born!, Right fork: %d, Left fork: %d.\n", philo->idx, forks[RIGHT], forks[LEFT]); */
	/* pthread_mutex_unlock(&philo->main->print_lock); */
	i = 0;
	if (philo->main->config.num_times_to_eat == -1)
		goal = LONG_MAX;
	else
		goal = philo->main->config.num_times_to_eat;
	while (i++ < goal)
	{
		grab_forks(philo, forks);
		eating(philo);
		down_forks(philo, forks);
		sleeping(philo);
	}
	return (NULL);
}

void	grab_forks(t_philo *philo, int *forks)
{
	pthread_mutex_lock(&philo->main->forks[forks[RIGHT]]);
	pthread_mutex_lock(&philo->main->print_lock);
	printf("%d philo %d has taken a fork.\n", calc_elapsed(philo->main->start_time), philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
	pthread_mutex_lock(&philo->main->forks[forks[LEFT]]);
	pthread_mutex_lock(&philo->main->print_lock);
	printf("%d philo %d has taken a fork.\n", calc_elapsed(philo->main->start_time), philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
}

void	down_forks(t_philo *philo, int *forks)
{
	pthread_mutex_lock(&philo->main->print_lock);
	pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
	printf("%d philo %d put down a fork.\n", calc_elapsed(philo->main->start_time), philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
	pthread_mutex_lock(&philo->main->print_lock);
	pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
	printf("%d philo %d put down a fork.\n", calc_elapsed(philo->main->start_time), philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->print_lock);
	printf("%d philo %d is eating.\n", calc_elapsed(philo->main->start_time), philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
	usleep(philo->main->config.time_to_eat);
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->print_lock);
	printf("%d philo %d is sleeping\n", calc_elapsed(philo->main->start_time), philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
	usleep(philo->main->config.time_to_sleep);
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
