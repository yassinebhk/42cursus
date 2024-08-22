/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr2_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:49:59 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/22 19:34:09 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr2_fd(char *s, int fd)
{
	int	i;
	int	check;

	i = -1;
	if (!s)
		check = write(fd, "(null)", 6);
	while (s[++i])
	{
		if (s[i] != '\'' && s[i] != '"')
			write(fd, &s[i], 1);
	}
	return (check);
}
