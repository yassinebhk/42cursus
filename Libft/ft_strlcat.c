/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:24:05 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/13 12:24:07 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	sizedst;
	size_t	sizesrc;

	i = 0;
	j = 0;
	while (dst[j] != '\0')
		j++;
	sizedst = j;
	sizesrc = (size_t)ft_strlen(src);
	if (size <= sizedst)
		return (sizesrc + size);
	while (*(dst + j) != '\0')
		j++;
	while (*(src + i) != '\0' && i < size - 1 - sizedst)
	{
		*(dst + j) = *(src + i);
		i++;
		j++;
	}
	*(dst + j) = '\0';
	return (sizedst + sizesrc);
}
