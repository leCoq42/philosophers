/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:43:08 by mhaan             #+#    #+#             */
/*   Updated: 2023/10/12 10:43:17 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	ph_atoi(const char *str)
{
	int64_t	val;
	int		sign;

	val = 0;
	sign = 1;
	if (!str)
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && *str > 47 && *str < 58)
		val = val * 10 + (*str++ - 48);
	return (val * sign);
}

void	ph_putstr_fd(const char *s, int fd)
{
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (*s)
		if (write(fd, s++, 1) == -1)
			return ;
}

void	*ph_calloc(size_t count, uint32_t size)
{
	void			*mem;
	unsigned char	*ptr;

	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	ptr = (unsigned char *)mem;
	while (size-- > 0)
		*ptr++ = '\0';
	return (mem);
}
