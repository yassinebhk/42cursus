/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:19:02 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/14 21:45:33 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_digs(int n)
{
	int	num;

	if (n == 0)
		return (0);
	num = 0;
	while (n != 0)
	{
		n = n / 10;
		num++;
	}
	return (num);
}

static char	*convert_str(char *num, long n, int i)
{
	static int	pos;

	if (!i)
		pos = 0;
	else
		pos = 1;
	if (n > 0)
	{
		convert_str(num, n / 10, pos);
		*(num + pos) = n % 10 + '0';
		pos++;
	}
	*(num + pos) = '\0';
	return (num);
}

char	*ft_itoa(int n)
{
	int		num_dig;
	char	*num;

	num_dig = num_digs(n);
	num = (char *)malloc((num_dig + 2) * sizeof(char));
	if (*num)
		return (NULL);
	if (n == 0)
	{
		*num = '0';
		*(num++) = '\0';
	}
	else if (n < 0)
	{
		*num = '-';
		num = convert_str(num, -(long)n, 1);
	}
	else
		num = convert_str(num, n, 0);
	return (num);
}
