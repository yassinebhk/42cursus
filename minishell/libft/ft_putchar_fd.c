/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:49:44 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/07 22:58:07 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, sizeof(char)) == -1)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	else
		return (1);
}
