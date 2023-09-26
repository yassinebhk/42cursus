/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:03:37 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/24 18:03:39 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_buffer(char *buffer, int *res, int *i)
{
	int	check;

	check = 1;
	while (*(buffer + *i) != '%' && *(buffer + *i))
	{
		check = write(1, buffer + *i, 1);
		if (!(check + 1))
			return (0);
		*res += check;
		(*i)++;
	}
	(*i)++;
	if (*(buffer + *i) && *(buffer + *i) == '%')
	{
		check = write(1, buffer + *i, 1);
		if (!(check + 1))
			return (0);
		*res += check;
	}
	if (!(*(buffer + *i)) && ft_putchar_fd(buffer[*i - 1], 1))
	{
		(*res)++;
		return (1);
	}
	return (check);
}

static int	printf_char_or_str(char c, va_list arg, int *res)
{
	int		check;
	char	letter;
	char	*str;

	check = 1;
	if (c == 'c')
	{
		letter = va_arg(arg, int);
		check = write(1, &letter, 1);
		if (!(check + 1))
			return (0);
		*res += check;
	}
	else
	{
		str = va_arg(arg, char *);
		check = ft_putstr_fd(str, 1);
		if (!(check + 1))
			return (0);
		*res += check;
	}
	return (check);
}

static char	*base(char c)
{
	char	*base_dec;
	char	*base_hex;
	char	*base_hex_may;

	base_dec = "0123456789";
	base_hex_may = "0123456789ABCDEF";
	base_hex = "0123456789abcdef";
	if (c == 'p' || c == 'x' || c == 'X')
	{
		if (c == 'X')
			return (base_hex_may);
		else
			return (base_hex);
	}
	else
		return (base_dec);
}

static int	printf_num(char c, va_list arg, int *res)
{
	int			check;
	long long	num;

	check = 1;
	if (c == 'p')
	{
		check = write(1, "0x", 2);
		if (!(check + 1))
			return (0);
		*res += check;
		num = va_arg(arg, long long);
		check = ft_putnbr_base(num, res, base(c));
		if (!check)
			return (0);
	}
	else
	{
		num = va_arg(arg, int);
		check = ft_putnbr_base(num, res, base(c));
		if (!check)
			return (0);
	}
	return (check);
}

struct		s_vars
{
	int		res;
	int		i;
};

int	ft_printf(char const *buffer, ...)
{
	va_list			arg;
	struct s_vars	a;

	a.i = 0;
	a.res = 0;
	va_start(arg, buffer);
	while (*(buffer + a.i))
	{
		if (!(print_buffer((char *)buffer, &a.res, &a.i)))
			return (-1);
		if (*(buffer + a.i) == 'c' || *(buffer + a.i) == 's')
		{
			if (!printf_char_or_str(*(buffer + a.i), arg, &a.res))
				return (-1);
		}
		else if (buffer[a.i] == 'x' || buffer[a.i] == 'X' || buffer[a.i] == 'd'
			|| buffer[a.i] == 'i' || buffer[a.i] == 'p' || buffer[a.i] == 'u')
		{
			if (!(printf_num(*(buffer + a.i), arg, &a.res)))
				return (-1);
		}
		a.i++;
	}
	va_end(arg);
	return (a.res);
}
