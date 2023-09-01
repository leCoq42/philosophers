#include "philo.h"


// int	gettimeofday(struct timeval *restrict tp, void *restrict tzp);

/* int	get_timestamp(struct timeval *time) */
/* { */
/* 	struct timeval	time_struct; */
/* 	int				timestamp; */
/**/
/* 	if (gettimeofday(time_struct, NULL) == -1) */
/* 		return (-1); */
/* 	timestamp = time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000; */
/* 	return (timestamp); */
/* } */

int	calc_elapsed(struct timeval start)
{
	struct timeval	cur;
	int				passed;

	
	if (gettimeofday(&cur, NULL) == -1)
		return (-1);
	passed = (cur.tv_sec - start.tv_sec) * 1000 + (cur.tv_usec - start.tv_usec) / 1000;
	return (passed);
}

/* int	main(void) */
/* { */
/* 	struct timeval start; */
/* 	int		time_elapsed; */
/**/
/* 	gettimeofday(&start, NULL); */
/* 	sleep(5); */
/* 	time_elapsed = calc_elapsed(start); */
/* 	printf("time_elapsed: %d ms\n", time_elapsed); */
/* 	return (0); */
/* } */
