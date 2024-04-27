/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:49:59 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/08 00:00:52 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	check;

	if (!s)
		check = write(fd, "(null)", 6);
	else
		check = write(fd, s, ft_strlen(s));
	if (check == -1)
		return (0);
	else
		return (1);
}
