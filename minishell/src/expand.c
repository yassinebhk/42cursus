/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:09:35 by maxgarci          #+#    #+#             */
/*   Updated: 2025/02/12 19:28:01 by maxgarci         ###   ########.fr       */
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

char	*strjoin_char(char *s1, char c, char terminator)
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
	new_str[i + 1] = terminator;
	return (free(s1), new_str);
}

static char	*find_var_value(t_env *env_list, char *var_name)
{
	while (env_list)
	{
		if (strcmp(env_list->key, var_name) == 0)
			return (env_list->var);
		env_list = env_list->next;
	}
	return (NULL);
}

static char	*expand_variable(t_node *tmp, char *str, int start, int end)
{
	char	*var_name;
	char	*var_value;
	char	*error_str;
	char	*concat_str;
	char	*final_str;

	if (ft_strlen(str) == 1)
		return (ft_strdup("$"));
	var_name = ft_strndup(str + start + 1, end - start - 1);
	if (!var_name)
		return (NULL);
	if (ft_strncmp(var_name, "?", 1) == 0 || ft_strncmp(var_name, "\\?",
			2) == 0)
	{
		if (ft_strncmp(var_name, "\\?", 2) == 0)
			start += 3;
		else
			start += 2;
		error_str = ft_itoa(tmp->status);
		free(var_name);
		if (str[start] != '\0')
		{
			concat_str = ft_strndup(str + start, ft_strlen(str) - start);
			final_str = ft_strjoin(error_str, concat_str);
			return (free(concat_str), free(error_str), final_str);
		}
		return (error_str);
	}
	var_value = find_var_value(tmp->var_list->env, var_name);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	return (ft_strdup(""));
}

static int	var_char_is_valid(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

static int	find_var_delimeter(char *str, int pos)
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

static char	*process_str(t_node *tmp, char *str)
{
	int		pos;
	int		var_end_pos;
	char	*new_arg;
	char	*var_value;
	size_t	i;

	pos = -1;
	new_arg = ft_strdup("");
	while (str[++pos])
	{
		if (str[0] != SINGLE_QUOTE && str[pos] == DOLLAR && (pos == 0 || str[pos - 1] != BACKSLASH))
		{
			var_end_pos = find_var_delimeter(str, pos);
			var_value = expand_variable(tmp, str, pos, var_end_pos);
			i = -1;
			while (var_value[++i] != '\0')
				new_arg = strjoin_char(new_arg, var_value[i], '\0');
			free(var_value);
			pos = var_end_pos - 1;
		}
		else if (str[pos] != SINGLE_QUOTE && str[pos] != DOUBLE_QUOTE)
			new_arg = strjoin_char(new_arg, str[pos], '\0');
	}
	return (new_arg);
}

static int	dollar_exists(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == DOLLAR)
			return (1);
		++i;
	}
	return (0);
}

int	expand_commands(t_node **head)
{
	int		i;
	int		arg_needs_expansion;
	t_node	*tmp;
	char	*expanded;

	tmp = *head;
	while (tmp)
	{
		i = -1;
		while (++i < tmp->content->num_args)
		{
			arg_needs_expansion = dollar_exists(tmp->content->args[i]);
			if (!arg_needs_expansion)
				continue;
			expanded = process_str(tmp, tmp->content->args[i]);
			free(tmp->content->args[i]);
			tmp->content->args[i] = ft_strdup(expanded);
		}
		tmp = tmp->next;
	}
	return (FN_SUCCESS);
}
