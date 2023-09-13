/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:39:54 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/13 16:43:33 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	char	letter;
	int		cont;

	cont = 0;
	letter = *src;
	while (letter != '\0')
	{
		*(dest + cont) = letter;
		letter = *(src + cont + 1);
		cont++;
	}
	*(dest + cont) = letter;
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*str;

	str = (char *)malloc(ft_strlen(s1) * sizeof(char));
	if (str == NULL)
		return (0);
	str = ft_strcpy(str, s1);
	return (str);
}
