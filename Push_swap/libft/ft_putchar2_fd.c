/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar2_fd.c                                    :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:49:44 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/14 21:49:46 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar2_fd(char c, int *res)
{
	if (write(1, &c, sizeof(char)) == -1)
		return (0);
	else
	{
		*res += 1;
		return (1);
	}
}
