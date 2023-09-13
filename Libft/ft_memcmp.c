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
	size_t	diff;
	size_t	cont;
	char	*a;
	char	*b;

	cont = 0;
	diff = 0;
	a = (char *)s1;
	b = (char *)s2;
	while (cont < n)
	{
		a++;
		b++;
		cont++;
	}
	if (*a != *b && cont < n)
		diff = *a - *b;
	return (diff);
}
