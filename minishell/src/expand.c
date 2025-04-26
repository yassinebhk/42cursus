/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:09:35 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/04/26 18:43:00 by maxgarci         ###   ########.fr       */
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

static char	*process_str(t_node *tmp, char *str, int last_status)
{
	int		pos;
	int		quotes;
	char	*new_arg;

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
		else if ((!quotes || quotes == 2) && str[pos] == DOLLAR
			&& (!ft_isspace(str[pos + 1]) && str[pos + 1] != DOUBLE_QUOTE))
			new_arg = load_variable(tmp, (char *[]){str, new_arg}, last_status,
					&pos);
		else
			new_arg = strjoin_char(new_arg, str[pos]);
	}
	return (new_arg);
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
			arg_needs_expansion = dollar_or_quotes(tmp->content->args[i]);
			if (!arg_needs_expansion)
				continue ;
			expanded = process_str(tmp, tmp->content->args[i],
					(*head)->last_status);
			if (!expanded)
				return (FN_FAILURE);
			free(tmp->content->args[i]);
			tmp->content->args[i] = ft_strdup(expanded);
			if (i == 0)
			{
				tmp->content->command = malloc(sizeof(char) * (strlen(tmp->content->args[0]) + 1));
				if (!tmp->content->command)
					return (perror(ENO_MEM_ERROR), FN_FAILURE);
				strcpy(tmp->content->command, tmp->content->args[0]);
			}
			free(expanded);
		}
		tmp = tmp->next;
	}
	return (FN_SUCCESS);
}
