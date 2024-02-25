/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:49:59 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/14 21:50:01 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int *res)
{
	int	check;

	if (!s)
		check = write(1, "(null)", 6);
	else
		check = write(1, s, ft_strlen(s));
	if (check == -1)
		return (0);
	else
	{
		*res += check;
		return (1);
	}
}
