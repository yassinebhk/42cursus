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

	a = (char *)dst;
	b = (char *)src;
	if (a != NULL && b != NULL)
	{
		while (n > 0)
		{
			*a = *b;
			a++;
			b++;
			n--;
		}
	}
	else
		return (NULL);
	return (dst);
}
