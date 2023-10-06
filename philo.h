#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

# define GRAB "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define DIED "died\n"
# define THINK "is thinking\n"

# define RIGHT 0
# define LEFT 1

# ifdef PRETTY_PRINT
#  define FORMAT "timer:%8ldms, philo %u %s"
# else
#  define FORMAT "%ld %u %s"
# endif

enum	e_philo_state
{
	ALIVE,
	DEAD,
	DONE
};

typedef struct s_config
{
	uint_fast8_t	num_philos;
	uint_fast32_t	time_to_die_ms;
	uint_fast32_t	time_to_eat_ms;
	uint_fast32_t	time_to_sleep_ms;
	uint_fast32_t	num_times_to_eat;
}	t_config;

typedef struct s_main
{
	t_config		config;
	uint_fast64_t	start_time;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	done_lock;
	uint_fast8_t	philos_done;
	bool			stop;
}	t_main;

typedef struct s_philo
{
	uint_fast8_t		id;
	enum e_philo_state	state;
	uint_fast64_t		last_meal_ms;
	pthread_t			thread;
	pthread_mutex_t		philo_lock;
	t_main				*main;
}	t_philo;

// PROTOTYPES
// init.c
t_main			*init_main(int argc, char **argv);

// free.c
void			free_all(t_main *main);
void			join_threads(t_main *main, uint_fast8_t num);
void			destroy_mutexes(t_main *main, uint_fast8_t num);

// philo.c
int				create_threads(t_main *main);
int				routine_loop(t_philo *philo, uint_fast8_t *forks, \
					uint_fast32_t goal, uint8_t uneven);
int				check_print(t_philo *philo, char *action);

// utils.c
long long		ph_atoi(const char *str);
void			ph_putnbr_fd(int n, int fd);
void			ph_putstr_fd(const char *s, int fd);
void			*ph_calloc(size_t count, uint_fast32_t size);

// time.c
uint_fast64_t	timestamp_ms(void);
uint_fast64_t	time_diff_ms(uint_fast64_t start_ms, uint_fast64_t cur_ms);
void			ph_sleep_ms(uint_fast32_t sleeptime_ms);

// error.c
/* void			error_exit(char *msg, int status); */
int				input_check(int argc, char **argv);

// observer.c
int				observer(t_main *main);

// actions.c
int				grab_forks(t_philo *philo, uint_fast8_t *forks);
int				eating(t_philo *philo, uint_fast8_t *forks);
int				sleeping(t_philo *philo);

#endif
