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
	str = (char *)malloc(len * sizeof(char));
	if (*str)
		return (NULL);
	while (len > 0)
	{
		*(str + cont) = *(s + start);
		start++;
		cont++;
		len--;
	}
	return (str);
}
