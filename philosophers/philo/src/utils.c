/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:33:11 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/13 13:06:43 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atoi(char *str)
{
	long long	num;
	int			cont;

	cont = 1;
	num = 0;
	while (((*str >= 9 && *str <= 13) || *str == 32) && *str != '\0')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			cont *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	return (num * cont);
}

long	get_time_in_ms(void)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (result);
}

void	ft_usleep(int time)
{
	long	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < time)
		usleep(time / 10);
}
