#include "philo.h"


// int	gettimeofday(struct timeval *restrict tp, void *restrict tzp);


int	get_start_time(long long *start_time)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	*start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (0);
}

int	calc_elapsed(int start_time)
{
	struct timeval	cur;
	long long		passed;
	
	if (gettimeofday(&cur, NULL) == -1)
		return (-1);
	passed = (cur.tv_sec * 1000 + cur.tv_usec / 1000) - start_time ;
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
