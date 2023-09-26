/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alumno <alumno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:07:00 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/26 10:07:05 by alumno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int char_in_base(char *base, long long num)
{
    int pos;

    pos = 0;
    while (*(base + pos))
    {
        if (*(base + pos) == num)
            return (pos);
        pos++;
    }
    return (0);
}

static int  ft_writenbr(long long num, int *res, char *base)
{
    int     check;
    char    c;
    
    check = 1;
    c = *(base + char_in_base(base, num));
    check = write(1, &c, 1);
    if (!(check + 1))
        return (0);
    *res += check;
    return (check);
}

int ft_putnbr_base(long long num, int *res, char *base)
{
    int     check;
    check = 1;
    if (num < 0)
    {
        check = write(1, "-", 1);
        if (!(check + 1))
            return (0);
        *res += check;
        ft_putnbr_base(-num, res, base);
    }
    else if (num > 0)
    {
        ft_putnbr_base(num / ft_strlen(base), res, base);
        if (!ft_writenbr(num % ft_strlen(base), res, base))
            return (0);
    }
    else
    {
        check = write(1, "0", 1);
        if (!(check + 1))
            return (0);
        *res += check;
    }
    return (check);   
}
