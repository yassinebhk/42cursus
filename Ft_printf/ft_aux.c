/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:06:24 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/30 18:43:01 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_fd(char *s, int *res)
{
	int	check;

	if (!s)
		check = write(1, "(null)", 6);
	else
		check = write(1, s, ft_strlen(s));
	if (check == -1)
		return (0);
	else
	{
		*res += check;
		return (1);
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	cont;

	cont = 0;
	while (s[cont] != '\0')
		cont++;
	return (cont);
}

int	ft_putchar_fd(char c, int *res)
{
	if (write(1, &c, sizeof(char)) == -1)
		return (0);
	else
	{
		*res += 1;
		return (1);
	}
}

int	putnbr(long long n, int *res, char *base)
{
	char	a;

	if (n > 0)
	{
		if (!putnbr(n / ft_strlen(base), res, base))
			return (0);
		a = *(base + char_in_base(base, n % ft_strlen(base)));
		if (write(1, &a, 1) <= 0)
			return (0);
		*res += 1;
	}
	return (1);
}

int	putptr(unsigned long long n, int *res, char *base)
{
	char	a;

	if (n > 0)
	{
		if (!putnbr(n / ft_strlen(base), res, base))
			return (0);
		a = *(base + char_in_base(base, n % ft_strlen(base)));
		if (write(1, &a, 1) <= 0)
			return (0);
		*res += 1;
	}
	return (1);
}
