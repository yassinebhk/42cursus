/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:03:52 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/24 18:03:54 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

struct		s_vars
{
	int		check;
	int		res;
	int		i;
	va_list	arg;
};

int			ft_putnbr_base(long long num, int *res, char *base);
int			ft_printf(char const *buffer, ...);

#endif
