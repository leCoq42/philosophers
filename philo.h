#ifndef PHILO_H
# define PHILO_H
	
# include	<stdlib.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<sys/time.h>
# include	<pthread.h>

# define USAGE "Error: Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

enum	t_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

enum	t_fork_state
{
	BUSY,
	FREE
}

typedef struct	s_philo
{
	int				idx;
	pthread_t		tid;
	t_state			state;
	int				time_of_last_meal;
}	t_philo

typedef struct	s_fork
{
	int				idx;
	pthread_mutex_t	lock;
}	t_fork

typedef struct	s_config
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
}	t_config

typedef struct	s_main
{
	t_config		config;
	t_fork			*forks;
	t_philo			*philos;
}	t_main;

t_main	*init_main(int argc, char **argv);
void	free_all(t_main **main);
void	free_philos(t_philos **philos);
void	*philo_func(void *arg);
long long	philo_atoi(const char *str);












#	endif
