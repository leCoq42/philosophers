#include "philo.h"

int_fast8_t	observer(t_main *main)
{
	/* size_t	idx; */

	/* idx = 0; */
	while (1)
	{
		pthread_mutex_lock(&main->obs_lock);
		if (main->state == DEAD || main->philos_done >= main->config.num_philos)
		{
			pthread_mutex_unlock(&main->obs_lock);
			return (1);
		}
		pthread_mutex_unlock(&main->obs_lock);
		/* idx = (idx + 1) % main->config.num_philos; */
		/* idx++; */
		/* if (idx == main->config.num_philos) */
		/* 	idx = 0; */
	}
	return (0);
}
/**/
/* void	stop_loop(t_main *main) */
/* { */
/**/
/**/
/**/
/**/
/* } */
