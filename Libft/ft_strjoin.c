/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:56:49 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/13 16:56:51 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	i;

	i = 0;
	while (*(dest + i) != '\0')
		i++;
	while (*src != '\0')
	{
		*(dest + i) = *src;
		i++;
		src++;
	}
	*(dest + i) = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;

	i = 0;
	s = (char *)malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char) + 1);
	if (!s)
		return (NULL);
	while (*(s1 + i) != '\0')
	{
		*(s + i) = *(s1 + i);
		i++;
	}
	*(s + i) = '\0';
	s = ft_strcat(s, (char *)s2);
	return (s);
}
// FREE DE S1 ¿?¿?¿?¿?