/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:14:25 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/17 18:50:33 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	cont;

	j = 0;
	i = 0;
	str = (char *)malloc(sizeof(char) * (strlen(s1) + 1));
	if (*str)
		return (NULL);
	while (ft_strchr(set, *(s1 + i)))
		i++;
	cont = i;
	i = 0;
	while (ft_strchr(set, *(s1 + strlen(s1) - 1 - i)))
		i++;
	while (j < strlen(s1) - i - cont)
	{
		*(str + j) = *(s1 + j + cont);
		j++;
	}
	return (str);
}
