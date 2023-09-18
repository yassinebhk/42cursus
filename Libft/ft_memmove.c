/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:07:34 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/13 11:40:24 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	int		i;

	d = (char *)dst;
	s = (char *)src;
	if (src < dst)
	{
		i = len - 1;
		while (i >= 0)
		{
			*(d + i) = *(s + i);
			i--;
		}
	}
	else if (src > dst)
	{
		i = 0;
		while ((size_t)i < len)
		{
			*(d + i) = *(s + i);
			i++;
		}
	}
	return (dst);
}
