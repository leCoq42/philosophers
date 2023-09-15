#include "philo.h"

static void	routine_loop(t_philo *philo, size_t	*forks, int64_t goal);
static void	grab_forks(t_philo *philo, size_t *forks, const uint8_t uneven);
static void	down_forks(t_philo *philo, size_t *forks, const uint8_t uneven);
static void	eating(t_philo *philo);
static void	sleeping(t_philo *philo);
static void	thinking(t_philo *philo);

int	philo_run(t_main *main)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&main->start_lock);
	while (i < main->config.num_philos)
	{
		if (pthread_create(&main->philos[i].thread, NULL, philo_func, &main->philos[i]) != 0)
			return (1);
		i++;
	}
	get_timestamp(&main->start_time);
	printf("start time:%ld\n", main->start_time);
	pthread_mutex_unlock(&main->start_lock);
	return (0);
}

void	*philo_func(void *arg)
{
	t_philo	*philo;
	size_t	forks[2];

	philo = (t_philo *)arg;
	forks[RIGHT] = philo->idx - 1;
	forks[LEFT] = philo->idx % philo->main->config.num_philos;
	pthread_mutex_lock(&philo->main->start_lock);
	pthread_mutex_unlock(&philo->main->start_lock);
	get_timestamp(&philo->timestamp);
	/* pthread_mutex_lock(&philo->main->print_lock); */
	/* printf("philo %zu's starttime: %ld\n", philo->idx, time); */
	/* printf("philo id: %zu, right fork: %zu, left fork: %zu\n", philo->idx, forks[RIGHT], forks[LEFT]); */
	/* pthread_mutex_unlock(&philo->main->print_lock); */
	routine_loop(philo, forks, philo->main->config.num_times_to_eat);
	pthread_mutex_lock(&philo->main->obs_lock);
	philo->main->philos_done++;
	pthread_mutex_unlock(&philo->main->obs_lock);
	return (NULL);
}

static void	routine_loop(t_philo *philo, size_t	*forks, int64_t goal)
{
	const uint8_t	uneven = philo->idx % 2;
	int64_t			i;
	uint64_t		time_elapsed;

	i = 0;
	while (1)
	{
		if (goal != -1 && i >= goal)
			break ;
		grab_forks(philo, forks, uneven);
		time_elapsed = calc_elapsed(philo->timestamp);
		if (time_elapsed >= philo->main->config.time_to_die)
		{
			pthread_mutex_lock(&philo->main->print_lock);
			printf("timer: %ldms, philo %zu has died.\n", calc_elapsed(philo->main->start_time), philo->idx);
			pthread_mutex_unlock(&philo->main->print_lock);
			philo->state = DEAD;
			down_forks(philo, forks, uneven);
			break ;
		}
		eating(philo);
		down_forks(philo, forks, uneven);
		sleeping(philo);
		thinking(philo);
		if (i == LONG_MAX)
			i = 0;
		else
			i++;
	}
}

static void	grab_forks(t_philo *philo, size_t *forks, const uint8_t uneven)
{
	if (uneven)
	{
		pthread_mutex_lock(&philo->main->print_lock);
		printf("timer: %ldms, philo %zu has taken a fork.\n", calc_elapsed(philo->main->start_time), philo->idx);
		pthread_mutex_unlock(&philo->main->print_lock);
		pthread_mutex_lock(&philo->main->forks[forks[RIGHT]]);
		pthread_mutex_lock(&philo->main->print_lock);
		printf("timer: %ldms, philo %zu has taken a fork.\n", calc_elapsed(philo->main->start_time), philo->idx);
		pthread_mutex_unlock(&philo->main->print_lock);
		pthread_mutex_lock(&philo->main->forks[forks[LEFT]]);
	}
	else
	{
		pthread_mutex_lock(&philo->main->print_lock);
		printf("timer: %ldms, philo %zu has taken a fork.\n", calc_elapsed(philo->main->start_time), philo->idx);
		pthread_mutex_unlock(&philo->main->print_lock);
		pthread_mutex_lock(&philo->main->forks[forks[LEFT]]);
		pthread_mutex_lock(&philo->main->print_lock);
		printf("timer: %ldms, philo %zu has taken a fork.\n", calc_elapsed(philo->main->start_time), philo->idx);
		pthread_mutex_unlock(&philo->main->print_lock);
		pthread_mutex_lock(&philo->main->forks[forks[RIGHT]]);
	}
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->print_lock);
	printf("timer: %ldms, philo %zu is eating.\n", calc_elapsed(philo->main->start_time), philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
	usleep(philo->main->config.time_to_eat);
	get_timestamp(&philo->timestamp);
	
}

static void	down_forks(t_philo *philo, size_t *forks, const uint8_t uneven)
{
	if (uneven)
	{
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
	}
	else
	{
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
	}
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->print_lock);
	printf("timer: %ldms, philo %zu is sleeping\n", calc_elapsed(philo->main->start_time), philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
	usleep(philo->main->config.time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->print_lock);
	printf("timer: %ldms, philo %zu is thinking.\n", calc_elapsed(philo->main->start_time), philo->idx);
	pthread_mutex_unlock(&philo->main->print_lock);
}

