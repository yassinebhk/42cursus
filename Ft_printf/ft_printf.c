/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alumno <alumno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:03:37 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/26 11:10:59 by alumno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include "limits.h"

size_t	ft_strlen(const char *s)
{
	size_t	cont;

	cont = 0;
	while (s[cont] != '\0')
		cont ++;
	return (cont);
}

int	ft_putstr_fd(char *s, int fd)
{	
	return (write(fd, s, ft_strlen(s)));
}

static int char_in_base(char *base, long long num)
{
    int pos;

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
    int     check;

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

int ft_putnbr_base(long long num, int *res, char *base)
{
    int     check;
    
    check = 1;
    if (num == 0)
    {
        check = write(1, "0", 1);
        if (!(check + 1))
            return (0);
        *res += check;
    }
    else if (num < 0)
    {
        check = write(1, "-", 1);
        if (!(check + 1))
            return (0);
        *res += check;
        putnbr(-num, res, base);
    }
    else
    {   
        if (!putnbr(num, res, base))
            return (0);
    }
    return (check);   
}

/*
*
*
*
*
*/

static int  print_buffer(char *buffer, int *res, int *i)
{   
    int check;

    check = 1;
    while (*(buffer + *i) != '%' && *(buffer + *i + 1))
    {
        check = write(1, buffer + *i, 1);
        if (!(check + 1))
            return (0);
        *res += check;
        (*i)++;
    }
    if (!(*(buffer + *i + 1)))
        return (0);
    (*i)++;
    if (*(buffer + *i) == '%')
    {   
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

static char *base (char c)
{
    char *base_dec;
    char *base_hex;
    char *base_HEX;

    base_dec = "0123456789";
    base_HEX = "0123456789ABCDEF";
    base_hex = "0123456789abcdef";
    if (c == 'p' || c == 'x' || c == 'X')
    {
        if (c == 'X')
            return (base_HEX);
        else 
            return (base_hex);
    }
    else
        return (base_dec);
}

static int  printf_num(char c, va_list arg, int *res)
{   
    int check;
    long long num;

    check = 1;
    if (c == 'p')
    {
        check = write(1, "0x", 2);
        if (!(check + 1))
            return (0);
        *res += check;
        num = va_arg(arg, long long);
        //printf("\n\nnum: %lld\n\n", num);
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
        if (!(print_buffer((char *)buffer, &res, &i)))
            return (-1);
        if (*(buffer + i) == 'c' || *(buffer + i) == 's')
        {
            if (!printf_char_or_str(*(buffer + i), arg, &res))
                return (-1);
        }
        else if (buffer[i] == 'x' || buffer[i] == 'X' || buffer[i] == 'd' 
                || buffer[i] == 'i' || buffer[i] == 'p' || buffer[i] == 'u')
        {
            if (!(printf_num(*(buffer + i), arg, &res)))
                return (-1);
        }
        i++;
    }
	va_end(arg);
    return (res);
}


int main ()
{
    char buffer[] = "";
    char *a = (char *)92233720368547758;
    printf("\n\n1: hola que tal %p\n\n", a);
    ft_printf("\n\nhola %p que tal %s\n\n", a, buffer);
}