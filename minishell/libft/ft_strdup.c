/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:39:54 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/19 16:07:15 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	char	letter;
	int		cont;

	cont = 0;
	if (!src)
		return (NULL);
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

	str = (char *)malloc((ft_strlen((char *)s1) + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	str = ft_strcpy(str, (char *)s1);
	return (str);
}
