#ifndef PHILO_H
# define PHILO_H
	
# include	<stdlib.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<sys/time.h>

# define USAGE "Error: Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef struct	s_philo
{
	int philo_id;
	int is_eating;
	int is_thinking;
	int is_sleeping;
	int is_dead;


} t_philo;







}
	






#	endif
