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

int	char_in_base(char *base, long long num)
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

static int	put_special(long long num, int *res, int u)
{
	int	check;

	check = 1;
	if (u && (num == LONG_MIN))
	{
		check = write(1, "8000000000000000", 16);
		if (!(check + 1))
			return (0);
		*res += check;
		return (-2);
	}
	return (check);
}

int	ft_putnbr_base(long long num, int *res, char *base, int u)
{
	int	check;

	if (num == 0)
	{
		if (write(1, "0", 1) <= 0)
			return (0);
		*res += 1;
	}
	check = put_special(num, res, u);
	if (!check)
		return (0);
	if (num < 0 && check)
	{
		if (write(1, "-", 1) <= 0)
			return (0);
		*res += 1;
		check = putnbr(-num, res, base);
	}
	else if (num > 0 && check)
	{
		if (!putnbr(num, res, base))
			return (0);
	}
	return (check);
}

int	ft_putptr_base(unsigned long long num, int *res, char *base)
{
	int	check;

	check = 1;
	if (num == 0)
	{
		if (write(1, "0", 1) <= 0)
			return (0);
		*res += 1;
	}
	else if (num == ULONG_MAX)
	{
		if (write(1, "ffffffffffffffff", 16) <= 0)
			return (0);
		*res += 16;
	}
	else
	{
		if (!putptr(num, res, base))
			return (0);
	}
	return (check);
}
