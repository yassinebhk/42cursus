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

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	while (len > 0)
	{
		*(d + i) = *(s + i);
		i++;
		len--;
	}
	return (dst);
}
