/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:04:37 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 12:03:30 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	num_words(char const *s, char c)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			num++;
			while (s[i] != c && s[i + 1])
				i++;
		}
		i++;
	}
	return (num);
}

static char	*fill_word(char *palabra, char *s, int ini, int pos)
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

static int	find_pos(char *palabra, char c, int *size, int *ini)
{	
	int	i;

	i = *ini + *size;
	*size = 0;
	while (palabra[i] && palabra[i] == c)
		(i)++;
	*ini = i;
	while (palabra[i] != c && palabra[i])
	{
		(*size)++;
		i++;
	}
	return (i);
}

void	ft_free_split(char **s)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		free(*(s + i));
		i++;
	}
	free(s);
}

char	**ft_split(char const *s, char c)
{
	struct s_vbs	a;

	a.i = 0;
	a.size = 0;
	a.ini = 0;
	a.palabra = (char **)malloc((num_words(s, c) + 1) * sizeof(char *));
	if (!a.palabra)
		return (NULL);
	while (a.i < num_words(s, c))
	{
		a.pos = find_pos((char *)s, c, &a.size, &a.ini);
		a.palabra[a.i] = (char *)malloc((a.size + 1) * sizeof(char));
		if (!a.palabra[a.i])
		{
			ft_free_split(a.palabra);
			return (NULL);
		}
		a.palabra[a.i] = fill_word(a.palabra[a.i], (char *)s, a.ini, a.pos);
		a.i++;
	}
	a.palabra[a.i] = NULL;
	return (a.palabra);
}
