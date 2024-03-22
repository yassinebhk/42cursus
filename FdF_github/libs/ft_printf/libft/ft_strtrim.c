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

static size_t	ft_size_word(char const *s1, char const *set, size_t *i,
		size_t *cont)
{
	while (ft_strchr(set, *(s1 + *i)) && *(s1 + *i))
		(*i)++;
	*cont = *i;
	if (*i == ft_strlen(s1))
		return (0);
	*i = 0;
	while (ft_strchr(set, *(s1 + ft_strlen(s1) - 1 - *i)))
		(*i)++;
	return (ft_strlen(s1) - *cont - *i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	cont;
	size_t	ini;

	j = 0;
	i = 0;
	cont = 0;
	if (!s1 || !set)
		return ((char *)s1);
	str = (char *)malloc(sizeof(char) * (ft_size_word(s1, set, &i, &cont) + 1));
	if (!str)
		return (NULL);
	ini = cont;
	while (cont < ft_strlen(s1) - i && cont != ft_strlen(s1))
	{
		*(str + j) = *(s1 + j + ini);
		j++;
		cont++;
	}
	str[j] = '\0';
	return (str);
}
