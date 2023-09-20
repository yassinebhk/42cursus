/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:28:46 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/12 16:54:38 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*a;
	char	*b;
	int		i;

	i = 0;
	a = (char *)dst;
	b = (char *)src;
	if (n == 0 || dst == src)
		return (dst);
	while (n > 0)
	{
		*(a + i) = *(b + i);
		i++;
		n--;
	}
	return (dst);
}
