/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:46 by maxgarci          #+#    #+#             */
/*   Updated: 2025/05/17 19:31:19 by maxgarci         ###   ########.fr       */
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
		valid_char = char_is_valid(str[next]);
		if (!valid_char)
			return (next);
		next++;
	}
	if (str[next - 1] == SINGLE_QUOTE || str[next - 1] == DOUBLE_QUOTE)
		return (next - 1);
	return (next);
}

char	*expand_variable(t_node *tmp, char *str, int arr[3])
{
	char	*var_name;
	char	*var_value;
	char	*error_str;

	var_name = ft_strndup(str + arr[0] + 1, arr[1] - arr[0] - 1);
	if (!var_name)
		return (NULL);
	if (ft_strncmp(var_name, "?", 1) == 0 || ft_strncmp(var_name, "\\?",
			2) == 0)
	{
		if (ft_strncmp(var_name, "\\?", 2) == 0)
			arr[0] += 3;
		else
			arr[0] += 2;
		error_str = ft_itoa(arr[2]);
		free(var_name);
		return (error_str);
	}
	var_value = find_var_value(tmp->var_list->env, var_name);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	return (ft_strdup(""));
}
