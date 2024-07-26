/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:03:52 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/20 12:54:14 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "Libft/libft.h"
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
