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

static int  format(char c, va_list arg, int res)
{   
    int res;

    if (c == '%')
    {
        res = write(1, &c, 1);
        if (!(res + 1))
            return (0);
    }
    else if(c == 'c' || c == 's')
    {
        return ();
    }
    else if(c == 'p')
    {
        return ();
    }
    else
    {
        return ();
    }
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
        if (*(buffer + i) != '%')
        {
            res += write(1, buffer + i, 1);
            if (!(res + 1))
                return (-1);
        }
        else
        {
            i++;
            res = format(*(buffer + i), arg, res);
            if (!res)
                return (-1);
            
        }
        i++;
    }
	va_end(arg);
    return (0);
}
