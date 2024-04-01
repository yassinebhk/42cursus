/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:50:44 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/14 21:50:46 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnbr(int n, int fd)
{
	char	a;

	if (n > 0)
	{
		putnbr(n / 10, fd);
		a = n % 10 + '0';
		write(fd, &a, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else if (n == INT_MIN)
	{
		write(fd, "-", 1);
		write(fd, "2", 1);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 0)
		putnbr(n, fd);
}
