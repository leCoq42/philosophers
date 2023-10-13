/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:42:40 by mhaan             #+#    #+#             */
/*   Updated: 2023/10/12 10:42:43 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_one_philo(t_main *main);

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc != 5 && argc != 6)
		return (print_usage_error(), 1);
	if (input_check(argc, argv))
		return (ph_putstr_fd("Invalid Input!\n", 1), 1);
	main = init_structs(argc, argv);
	if (!main)
		return (ph_putstr_fd("Init error!\n", 2), free_all(main), 1);
	if (main->config.num_philos == 1)
		print_one_philo(main);
	else
	{
		if (create_threads(main) == 1)
			return (free_all(main), 1);
		observer(main);
	}
	end_program(main);
}

void	print_one_philo(t_main *main)
{
	printf("0 1 has taken a fork\n");
	ph_sleep_ms(main->config.tt_die_ms, main);
	printf("%u 1 died\n", main->config.tt_die_ms);
}
