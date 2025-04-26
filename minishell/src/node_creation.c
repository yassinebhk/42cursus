/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:44:36 by maxgarci          #+#    #+#             */
/*   Updated: 2025/04/26 18:43:42 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	skip_argument(char *str, int *read_pos)
{
	int	squote_opened;
	int	dquote_opened;
	int	in_quotes;

	squote_opened = 0;
	dquote_opened = 0;
	in_quotes = 0;
	while ((str[*read_pos] && !ft_isspace(str[*read_pos]) && !is_redir(str,
				*read_pos)) || squote_opened || dquote_opened)
	{
		if (!in_quotes && (squote_opened || dquote_opened))
			in_quotes = 1;
		check_quotes(str[*read_pos], &squote_opened, &dquote_opened);
		++(*read_pos);
	}
}

static void	count_args_redir(char *str, int *n_args, int *n_redir)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		if (is_redir(str, pos))
		{
			while (is_redir(str, pos))
				pos++;
			while (ft_isspace(str[pos]))
				pos++;
			while (str[pos] > ' ' && !is_redir(str, pos))
				pos++;
			(*n_redir)++;
		}
		else
		{
			skip_argument(str, &pos);
			(*n_args)++;
		}
		clear_spaces(str, &pos);
	}
}

static int	parse_arg(char *str, t_command **command, int *i, int *args_pos)
{
	int	cp_i;
	int	new_arg_index;

	cp_i = 0;
	new_arg_index = *i;
	skip_argument(str, i);
	(*command)->args[*args_pos] = (char *)malloc(sizeof(char) * ((*i)
				- new_arg_index + 1));
	if (!(*command)->args[*args_pos])
		return (perror(ENO_MEM_ERROR), ENO_MEM);
	while (new_arg_index < *i)
		(*command)->args[*args_pos][cp_i++] = str[new_arg_index++];
	(*command)->args[(*args_pos)++][cp_i] = '\0';
	if ((*args_pos) == 1)
	{
		(*command)->command = malloc(sizeof(char) * (strlen((*command)->args[0])
					+ 1));
		if (!(*command)->command)
			return (perror(ENO_MEM_ERROR), FN_FAILURE);
		strcpy((*command)->command, (*command)->args[0]);
	}
	return (FN_SUCCESS);
}

static int	create_command(char *str, t_command **command)
{
	int	redir_pos;
	int	args_pos;
	int	i;

	redir_pos = 0;
	args_pos = 0;
	i = 0;
	while (str[i])
	{
		if (is_redir(str, i))
		{
			if (parse_redir(str, command, &i, &redir_pos))
				return (PARSING);
		}
		else
		{
			if (parse_arg(str, command, &i, &args_pos))
				return (ENO_MEM);
		}
		clear_spaces(str, &i);
	}
	return (FN_SUCCESS);
}

int	new_command(char *str, t_command **command)
{
	int	n_args;
	int	n_redir;

	n_args = 0;
	n_redir = 0;
	count_args_redir(str, &n_args, &n_redir);
	(*command)->num_args = n_args;
	(*command)->num_redir = n_redir;
	(*command)->args = (char **)malloc(sizeof(char *) * ((*command)->num_args
				+ 1));
	if (!(*command)->args)
		return (perror(ENO_MEM_ERROR), FN_FAILURE);
	(*command)->args[n_args] = NULL;
	if (n_redir)
	{
		(*command)->redir = (t_redir **)malloc(sizeof(t_redir *) * n_redir);
		if (!(*command)->redir)
			return (perror(ENO_MEM_ERROR), FN_FAILURE);
	}
	else
		(*command)->redir = NULL;
	if (create_command(str, command))
		return (perror(PARSING_ERROR), FN_FAILURE);
	return (FN_SUCCESS);
}
