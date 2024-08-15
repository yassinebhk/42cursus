/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:04:37 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/15 20:40:30 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_word(char *palabra, const char *s, int ini, int pos)
{
	int	j;

	j = 0;
	while (ini < pos)
	{
		palabra[j] = s[ini];
		j++;
		ini++;
	}
	palabra[j] = '\0';
	return (palabra);
}

int	find_first_delimiter(const char *s, char c)
{
	int pos = 0;

	while (s[pos] && s[pos] != c)
		pos++;
	return (pos);
}

void	free_memory(char **palabra, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(palabra[i]);
		i++;
	}
	free(palabra);
}

char	**allocate_and_fill(const char *s, int pos, int len)
{
	char **palabra;

	palabra = (char **)malloc(3 * sizeof(char *));
	if (!palabra)
		return (NULL);
	palabra[0] = (char *)malloc((pos + 1) * sizeof(char));
	if (!palabra[0])
		return (free_memory(palabra, 0), NULL);
	palabra[1] = (char *)malloc((len - pos) * sizeof(char));
	if (!palabra[1])
		return (free_memory(palabra, 1), NULL);
	fill_word(palabra[0], s, 0, pos);
	fill_word(palabra[1], s, pos + 1, len);
	palabra[2] = NULL;
	return (palabra);
}

char	**ft_split(const char *s, char c)
{
	int pos;
	int len;

	len = 0;
	while (s[len])
		len++;
	pos = find_first_delimiter(s, c);
	if (pos >= len) {
		return NULL;
	}
	return (allocate_and_fill(s, pos, len));
}
