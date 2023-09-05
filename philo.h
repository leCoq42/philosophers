#ifndef PHILO_H
# define PHILO_H
	
# include	<stdlib.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<string.h>
# include	<sys/time.h>
# include	<pthread.h>
# include	<limits.h>

# define USAGE "Error: Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define RIGHT 0
# define LEFT 1

enum	t_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct	s_config
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_to_eat;
}	t_config;

typedef struct	s_main
{
	t_config		*config;
	pthread_mutex_t	**forks;
	pthread_mutex_t	print_lock;
	struct s_philo	**philos;
	int				start_time;
}	t_main;

typedef struct	s_philo
{
	int					idx;
	pthread_t			tid;
	enum t_philo_state	state;
	int					time_of_last_meal;
	t_main				*main;
}	t_philo;

t_main		*init_main(int argc, char **argv);
void		free_all(t_main *main);
void		*philo_func(void *arg);
long long	philo_atoi(const char *str);
int			calc_elapsed(int start_time);
int			get_start_time(int *start_time);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(const char *s, int fd);
/* void		write_synced(t_philo *philo); */
void		grab_forks(t_philo *philo, int *forks);
void		down_forks(t_philo *philo, int *forks);







#	endif
