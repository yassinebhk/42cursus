/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:09:35 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/03/21 09:58:28 by maxgarci         ###   ########.fr       */
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

static char	*expand_variable(t_node *tmp, char *str, int arr[3])
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

static int	var_char_is_valid(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
			|| c == '_' || c == '?');
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

static char	*process_str(t_node *tmp, char *str, int last_exit_status)
{
	int		pos;
	int		var_end_pos;
	int		i;
	int		quotes;
	char	*new_arg;
	char	*var_value;

	pos = -1;
	quotes = 0;
	new_arg = ft_strdup("");
	while (str[++pos])
	{
		if (!quotes && str[pos] == SINGLE_QUOTE)
			quotes = 1;
		else if (!quotes && str[pos] == DOUBLE_QUOTE)
			quotes = 2;
		else if (quotes == 1 && str[pos] == SINGLE_QUOTE)
			quotes = 0;
		else if (quotes == 2 && str[pos] == DOUBLE_QUOTE)
			quotes = 0;
		else if ((!quotes || quotes == 2) && str[pos] == DOLLAR \
				&& str[pos - 1] != BACKSLASH && (!ft_isspace(str[pos + 1]) \
				&& str[pos + 1] != DOUBLE_QUOTE))
		{
			var_end_pos = find_var_delimeter(str, pos);
			var_value = expand_variable(tmp, str, (int[]){pos, var_end_pos, last_exit_status});
			i = -1;
			while (var_value[++i] != '\0')
				new_arg = strjoin_char(new_arg, var_value[i], '\0');
			free(var_value);
			pos = var_end_pos - 1;
		}
		else
			new_arg = strjoin_char(new_arg, str[pos], '\0');
	}
	return (new_arg);
}

static int	dollar_or_quotes(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == DOLLAR || arg[i] == SINGLE_QUOTE || 
			arg[i] == DOUBLE_QUOTE)
			return (1);
		++i;
	}
	return (0);
}

int	expand_commands(t_node **head, int last_exit_status)
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
			arg_needs_expansion = dollar_or_quotes(tmp->content->args[i]);
			if (!arg_needs_expansion)
				continue ;
			expanded = process_str(tmp, tmp->content->args[i], \
									last_exit_status);
			free(tmp->content->args[i]);
			tmp->content->args[i] = ft_strdup(expanded);
		}
		tmp = tmp->next;
	}
	return (FN_SUCCESS);
}
