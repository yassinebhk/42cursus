/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:43:12 by maxgarci          #+#    #+#             */
/*   Updated: 2025/04/27 14:45:31 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*strjoin_char(char *s1, char c)
{
	size_t	len1;
	size_t	i;
	char	*new_str;

	len1 = ft_strlen(s1);
	new_str = (char *)malloc(len1 + 2);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < len1)
		new_str[i] = s1[i];
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (free(s1), new_str);
}

int	find_var_delimeter(char *str, int pos)
{
	int	next;
	int	valid_char;

	next = pos + 1;
	while (str[next])
	{
		valid_char = var_char_is_valid(str[next]);
		if (!valid_char)
			return (next);
		next++;
	}
	if (str[next - 1] == SINGLE_QUOTE || str[next - 1] == DOUBLE_QUOTE)
		return (next - 1);
	return (next);
}
