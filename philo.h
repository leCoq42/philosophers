#ifndef PHILO_H
# define PHILO_H
	
#include	<stddef.h>
#include	<stdint.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<string.h>
#include	<sys/time.h>
#include	<pthread.h>
#include	<limits.h>

#define USAGE "Error: Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
#define RIGHT 0
#define LEFT 1

enum	t_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	DONE
};

typedef struct	s_config
{
	size_t		num_philos;
	uint64_t	time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int64_t		num_times_to_eat;
}	t_config;

typedef struct	s_main
{
	t_config		config;
	int64_t			start_time;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	obs_lock;
	uint8_t			philos_done;
}	t_main;

typedef struct	s_philo
{
	size_t				idx;
	int64_t				timestamp;
	pthread_t			thread;
	enum t_philo_state	state;
	int64_t				time_of_last_meal;
	t_main				*main;
}	t_philo;

t_main	*init_main(int argc, char **argv);
void	free_all(t_main *main);
int		philo_run(t_main *main);
void	*philo_func(void *arg);
int		ph_atoi(const char *str);
int64_t	calc_elapsed(int64_t start_time);
int64_t	get_timestamp(int64_t *start_time);
void	ph_putnbr_fd(int n, int fd);
void	ph_putstr_fd(const char *s, int fd);
void	error_exit(char *msg, int status);
int8_t	observer(t_main *main);
void	*ph_calloc(size_t count, size_t size);


#	endif
