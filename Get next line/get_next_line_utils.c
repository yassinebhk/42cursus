/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:22:28 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/10/09 22:08:01 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	size_t	cont;

	cont = 0;
	if (!s)
		return (0);
	while (s[cont] != '\0')
		cont++;
	return (cont);
}

static char	*ft_strcat(char *dest, char *src, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*(dest + i) != '\0')
		i++;
	while (*src != '\0' && j < size)
	{
		*(dest + i) = *src;
		i++;
		src++;
		j++;
	}
	*(dest + i) = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2, int size, int mlc)
{
	char	*s;
	int		i;

	i = 0;
	s = (char *)malloc((ft_strlen(s1) + size + 1) * sizeof(char));
	if (!s)
		return (free(s2), free(s1), NULL);
	while (*(s1 + i) != '\0')
	{
		*(s + i) = *(s1 + i);
		i++;
	}
	*(s + i) = '\0';
	s = ft_strcat(s, (char *)s2, size);
	if (!mlc)
		return (free(s2), free(s1), s);
	else
		return (free(s1), s);
}

char	*ft_substr(char *s, int start, int len, int free_str)
{
	int		cont;
	char	*str;

	cont = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (start + len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		*str = '\0';
		if (free_str)
			return (free(s), str);
		else
			return (str);
	}
	while (len > 0 && *(s + start))
	{
		*(str + cont) = *(s + start);
		(free(NULL), start++, cont++, len--);
	}
	*(str + cont) = '\0';
	if (free_str)
		return (free(s), str);
	else
		return (str);
}

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)c == s[i])
			return (i);
		i++;
	}
	if ((unsigned char)c == s[i])
		return (i);
	else
		return (-1);
}
