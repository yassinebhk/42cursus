/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:44:08 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/13 16:44:10 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int				cont;
	char			*str;

	cont = 0;
	if (start >= ft_strlen (s))
		len = 0;
	else if (start + len >= ft_strlen (s))
		len = ft_strlen (s) - start + 1;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (start >= ft_strlen (s))
	{
		*str = '\0';
		return (str);
	}
	while (len > 0 && *(s + start))
	{
		*(str + cont) = *(s + start);
		start++;
		cont++;
		len--;
	}
	*(str + cont) = '\0';
	return (str);
}
