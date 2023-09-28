/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:07:00 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/25 18:07:03 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	char_in_base(char *base, long long num)
{
	int	pos;

	pos = 0;
	while (*(base + pos))
	{
		if (pos == num)
			return (pos);
		pos++;
	}
	return (0);
}

static int	putnbr(long long n, int *res, char *base)
{
	char	a;
	int		check;

	check = 1;
	if (n > 0)
	{
		putnbr(n / ft_strlen(base), res, base);
		a = *(base + char_in_base(base, n % ft_strlen(base)));
		check = write(1, &a, 1);
		if (!(check + 1))
			return (0);
		*res += check;
		return (check);
	}
	return (check);
}

static int	put_special(long long num, int *res)
{
	int	check;

	check = 1;
	if (num == 0)
	{
		check = write(1, "0", 1);
		if (!(check + 1))
			return (0);
		*res += check;
		return (-2);
	}
	else if (num == LONG_MIN)
	{	
		if (num == LONG_MIN)
			check = write(1, "8000000000000000", 16);
		else
			check = write(1, "ffffffffffffffff", 16);
		if (!(check + 1))
			return (0);
		*res += check;
		return (-2);
	}
	return (check);
}

int	ft_putnbr_base(long long num, int *res, char *base)
{
	int	check;

	check = put_special(num, res);
	if (!check)
		return (0);
	if (num < 0 && !(check - 1))
	{
		check = write(1, "-", 1);
		if (!(check + 1))
			return (0);
		*res += check;
		putnbr(-num, res, base);
	}
	else if (num > 0 && !(check - 1))
	{
		if (!putnbr(num, res, base))
			return (0);
	}
	return (check);
}
