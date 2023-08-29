#ifndef PHILO_H
# define PHILO_H
	
# include	<stdlib.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<sys/time.h>
# include	<pthread.h>

# define USAGE "Error: Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

enum	t_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct	s_philo
{
	pthread_t		tid;
	enum t_state	state
	int				sleep_time;
}	t_philo;




t_philo	*init_philo(int idx);











#	endif
