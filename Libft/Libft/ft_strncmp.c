/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:40:55 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/13 13:40:57 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	diff;
	size_t	cont;

	cont = 0;
	diff = 0;
	while (*s1 == *s2 && *s1 != 0 && cont < n)
	{
		s1++;
		s2++;
		cont++;
	}
	if (*s1 != *s2 && cont < n)
		diff = *s1 - *s2;
	return (diff);
}
