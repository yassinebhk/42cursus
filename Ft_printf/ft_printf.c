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

// t_list
// putbr base
// long long ; punteros
// empezar
// end

#include "ft_printf.h"

static int  print_per(char *buffer, int *res, int *i)
{   
    int check;

    check = 1;
    while (*(buffer + *i) != '%' && *(buffer + *i))
    {
        check = write(1, buffer + *i, 1);
        if (!(check + 1))
            return (0);
        *res += check;
        i++;
    }
    if (*(buffer + *i) && *(buffer + *i + 1) == '%')
    {   
        i++;
        check = write(1, buffer + *i, 1);
        if (!(check + 1))
            return (0);
        *res += check;
    }
    return (check);
}

static int  printf_char_or_str(char c, va_list arg, int *res)
{
    int     check;
    char    letter;
    char    *str;

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

static int  printf_num(char c, va_list arg, int *res)
{   
    int check;
    long long num;

    check = 1;
    if (c == 'p')
    {

    }
    else 
    {
        num = va_arg(arg, int);
        check = ft_putnbr_base(num, arg, res, base(c));
        if (!check)
            return (-1);
    }
    return (check);
}

int ft_printf(char const *buffer, ...)
{
	va_list	arg;
	int		res;
    int     i;

    i = 0;
    res = 0;
	va_start(arg, buffer);
    while (*(buffer + i))
    {   
        if (!(print_per(*(buffer + i), &res, &i)))
            return (-1);
        if (*(buffer + i) == 'c' || *(buffer + i) == 's')
        {
            if (!printf_char_or_str(*(buffer + i), arg, &res));
                return (-1);
        }
        else 
        {
            if (!(printf_num(*(buffer + i), arg, &res)))
                return (-1);
        }
        i++;
    }
	va_end(arg);
    return (res);
}

