/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:54:37 by maxgarci          #+#    #+#             */
/*   Updated: 2025/05/17 20:31:34 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_type_redir(char *str, int *pos, t_redir *redir)
{
	if (!redir)
		return (ft_putstr_fd(ENO_MEM_ERROR, 2), FN_FAILURE);
	if (str[*pos] == '>' && str[*pos + 1] == '>')
		redir->type = r_append;
	else if (str[*pos] == '>')
		redir->type = r_output;
	else if (str[*pos] == '<' && str[*pos + 1] == '<')
		redir->type = r_heredoc;
	else if (str[*pos] == '<')
		redir->type = r_input;
	else if (!char_is_valid(str[*pos + 2]))
		return (free(redir), ft_putstr_fd(PARSING_ERROR, 2), FN_FAILURE);
	while (is_redir(str, *pos))
		(*pos)++;
	while (ft_isspace(str[*pos]))
		(*pos)++;
	return (FN_SUCCESS);
}

static int	init_variables(char **filename, int *quotes)
{
	*filename = ft_strdup("");
	*quotes = 0;
	if (!*filename)
		return (ft_putstr_fd(ENO_MEM_ERROR, 2), FN_FAILURE);
	return (FN_SUCCESS);
}

static char	*parse_redir_filename(char *str, int *i)
{
	char	*filename;
	int		quotes;

	if (init_variables(&filename, &quotes))
		return (NULL);
	while (str[*i] > ' ' || quotes)
	{
		if (str[*i] == SINGLE_QUOTE && quotes == 1)
			quotes = 0;
		else if (str[*i] == SINGLE_QUOTE && quotes == 0)
			quotes = 1;
		else if (str[*i] == DOUBLE_QUOTE && quotes == 2)
			quotes = 0;
		else if (str[*i] == DOUBLE_QUOTE && quotes == 0)
			quotes = 2;
		if (char_is_valid(str[*i]) || quotes)
			filename = strjoin_char(filename, str[(*i)]);
		else
			return (ft_putstr_fd(BAD_ASSIGNMENT_ERROR, 2), free(filename),
				NULL);
		(*i)++;
	}
	filename = strjoin_char(filename, '\0');
	return (filename);
}

static t_redir	*create_redir(char *str, int *i)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (ft_putstr_fd(ENO_MEM_ERROR, 2), NULL);
	if (handle_type_redir(str, i, redir))
		return (free(redir), NULL);
	redir->filename = parse_redir_filename(str, i);
	if (!redir->filename)
		return (free(redir), NULL);
	return (redir);
}

int	parse_redir(char *str, t_command **command, int *i, int *redir_pos)
{
	(*command)->redir[*redir_pos] = create_redir(str, i);
	if (!((*command)->redir[(*redir_pos)++]))
		return (PARSING);
	return (FN_SUCCESS);
}
