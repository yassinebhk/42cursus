/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:10:45 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/13 12:10:47 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	cont;
	size_t	n;
	size_t	tam;

	tam = size;
	n = (size_t)ft_strlen(src);
	cont = 0;
	while (cont < tam && *(src + cont) != '\0')
	{
		*(dst + cont) = *(src + cont);
		cont++;
	}
	*(dst + size - 1) = '\0';
	while (cont < tam)
	{
		*(dst + cont) = '\0';
		cont++;
	}
	return (n);
}
