/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:35:02 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/13 13:35:04 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	p = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)c == s[i])
			p = ((char *)s + i);
		i++;
	}
	if ((unsigned char)c == s[i])
		return ((char *)s + i);
	return (p);
}
