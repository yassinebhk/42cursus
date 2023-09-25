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

char *base (char c)
{
    char *base_dec;
    char *base_hex;
    char *base_HEX;

    base_dec = "0123456789";
    base_HEX = "0123456789ABCDEF";
    base_hex = "0123456789abcdef";
    if (c == 'p' || c == 'x' || c == 'X')
    {
        if (c == 'e')
        ;
            //devuelvo lo que searchfs
        //devuelvo lo otro
    }
}

int ft_putnbr_base(long long num, va_list arg, int *res, char *base)
{
    int check;

    check = 0;
}
