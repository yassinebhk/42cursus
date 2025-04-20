/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:27:15 by maxgarci          #+#    #+#             */
/*   Updated: 2025/04/20 13:06:10 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new_str;
	size_t	i;

	len = 0;
	while (s[len] && len < n)
		len++;
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < len)
		new_str[i] = s[i];
	new_str[len] = '\0';
	return (new_str);
}

int	var_char_is_valid(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
		|| c == '?');
}

int	dollar_or_quotes(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == DOLLAR || arg[i] == SINGLE_QUOTE
			|| arg[i] == DOUBLE_QUOTE)
			return (1);
		++i;
	}
	return (0);
}

char	*find_var_value(t_env *env_list, char *var_name)
{
	while (env_list)
	{
		if (strcmp(env_list->key, var_name) == 0)
			return (env_list->var);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*load_variable(t_node *tmp, char **strings, int last_status, int *pos)
{
	int		i;
	int		var_end_pos;
	char	*var_value;

	var_end_pos = find_var_delimeter(strings[0], *pos);
	var_value = expand_variable(tmp, strings[0], (int []){*pos, var_end_pos,
			last_status});
	if (!var_value)
		return (strings[1]);
	i = -1;
	while (var_value[++i] != '\0')
		strings[1] = strjoin_char(strings[1], var_value[i], '\0');
	free(var_value);
	*pos = var_end_pos - 1;
	return (strings[1]);
}
