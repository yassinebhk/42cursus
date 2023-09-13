/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:58:57 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/13 13:58:59 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *neddle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (neddle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		while (haystack[i + j] == neddle[j] && haystack[i + j] != '\0'
			&& j < len)
			j++;
		if (neddle[j] == '\0')
			return ((char *)haystack + i);
		i++;
		j = 0;
		len--;
	}
	return (NULL);
}
