/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:03:52 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/02/25 19:06:15 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

struct		s_vars
{
	int		check;
	int		res;
	int		i;
	va_list	arg;
};

int			ft_putptr_base(unsigned long long num, int *res, char *base);
int			ft_putnbr_base(long long num, int *res, char *base, int u);
int			ft_printf(char const *buffer, ...);
int			putptr(unsigned long long n, int *res, char *base);
int			putnbr(long long n, int *res, char *base);
int			char_in_base(char *base, long long num);

#endif
