/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:17:46 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/05/04 10:35:30 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

long	ft_atoi_mod(const char *nptr, int *error)
{
	long	num;
	int		sign;
	int		i;

	i = 0;
	*error = 0;
	while (ft_isspace(nptr[i]))
		++i;
	sign = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			sign = -1;
	num = 0;
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		*error = 1;
		num *= 10;
		num += nptr[i] - '0';
		++i;
	}
	if (nptr[i] && !ft_isdigit(nptr[i]))
		*error = 0;
	return ((num * sign));
}

int	ft_strchr_mod(int *s, int pos, int c)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_integer(char *str)
{
	while (*str)
	{
		if ((*str < '0' || *str > '9') && *str != '-' && *str != '+')
			return (0);
		str++;
	}
	return (1);
}
