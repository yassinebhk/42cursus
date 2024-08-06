/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:33:11 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/06 18:34:33 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atoi(char *str)
{
	long	num;
	int		cont;

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