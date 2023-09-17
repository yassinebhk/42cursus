/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:52:42 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/13 13:52:44 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		diff;
	size_t	cont;
	char	*a;
	char	*b;

	cont = 0;
	diff = 0;
	a = (char *)s1;
	b = (char *)s2;
	while (cont < n && *a == *b && *a != 0)
	{
		a++;
		b++;
		cont++;
	}
	if (*a != *b && cont < n)
		diff = (unsigned char)(*a) - (unsigned char)(*b);
	return (diff);
}
