/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:03:37 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/22 19:29:37 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	int					check;
	long long			num;
	unsigned long long	unum;

	check = 1;
	if (c == 'p')
	{
		check = write(1, "0x", 2);
		if (!(check + 1))
			return (0);
		*res += check;
		unum = va_arg(arg, unsigned long long);
		return (ft_putptr_base(unum, res, base(c)));
	}
	else if (c == 'u' || c == 'x' || c == 'X')
	{
		unum = va_arg(arg, unsigned int);
		return (ft_putptr_base(unum, res, base(c)));
	}
	else
	{
		num = va_arg(arg, int);
		return (ft_putnbr_base(num, res, base(c), 0));
	}
}

static int	format(char c, int *res, va_list arg)
{
	if (c == '%')
		return (ft_putchar2_fd('%', res));
	else if (c == 'c')
		return (ft_putchar2_fd(va_arg(arg, int), res));
	else if (c == 's')
		return (ft_putstr2_fd(va_arg(arg, char *), 1));
	else
		return (printf_num(c, arg, res));
}

static int	print_buff(char *buff, int *res, int *i, va_list arg)
{
	int	check;

	check = 1;
	while (*(buff + *i) != '%' && *(buff + *i))
	{
		check = write(1, buff + *i, 1);
		if (!(check + 1))
			return (0);
		*res += check;
		(*i)++;
	}
	if (!*(buff + *i))
		return (-1);
	else
		return (format(*(buff + *i + 1), res, arg));
}

int	ft_printf(char const *buff, ...)
{
	struct s_vars	a;

	a.i = 0;
	a.res = 0;
	va_start(a.arg, buff);
	while (*(buff + a.i))
	{
		a.check = print_buff((char *)buff, &a.res, &a.i, a.arg);
		if (!a.check)
			return (-1);
		else if (!(a.check + 1))
			break ;
		a.i += 2;
	}
	va_end(a.arg);
	return (a.res);
}
