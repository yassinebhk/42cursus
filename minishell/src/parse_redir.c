/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:54:37 by maxgarci          #+#    #+#             */
/*   Updated: 2025/04/20 12:57:06 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redir(char *str, int pos)
{
	return ((str[pos] == '>' && str[pos + 1] == '>') || str[pos] == '>'
		|| (str[pos] == '<' && str[pos + 1] == '<') || str[pos] == '<');
}

static inline int	valid_char_filename(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '-'
		|| c == '_' || c == '.' || ((c >= '0') && (c <= '9')));
}

static int	handle_type_redir(char *str, int *pos, t_redir *redir)
{
	if (!redir)
		return (perror(ENO_MEM_ERROR), FN_FAILURE);
	if (str[*pos] == '>' && str[*pos + 1] == '>')
		redir->type = r_append;
	else if (str[*pos] == '>')
		redir->type = r_output;
	else if (str[*pos] == '<' && str[*pos + 1] == '<')
		redir->type = r_heredoc;
	else if (str[*pos] == '<')
		redir->type = r_input;
	else if (!valid_char_filename(str[*pos + 2]))
		return (free(redir), perror(PARSING_ERROR), FN_FAILURE);
	while (is_redir(str, *pos))
		(*pos)++;
	while (ft_isspace(str[*pos]))
		(*pos)++;
	return (FN_SUCCESS);
}

static t_redir	*create_redir(char *str)
{
	int		i;
	int		begin;
	int		cp_i;
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	i = 0;
	if (handle_type_redir(str, &i, redir))
		return (NULL);
	begin = i;
	if (!valid_char_filename(str[i]))
		return (perror(BAD_ASSIGNMENT_ERROR), free(redir), NULL);
	while (str[i] > ' ' && !is_redir(str, i))
	{
		if (!valid_char_filename(str[i++]))
			return (perror(BAD_ASSIGNMENT_ERROR), free(redir), NULL);
	}
	redir->filename = (char *)malloc(sizeof(char) * (i - begin + 1));
	if (!redir->filename)
		return (perror(ENO_MEM_ERROR), free(redir), NULL);
	cp_i = 0;
	while (begin < i)
		redir->filename[cp_i++] = str[begin++];
	redir->filename[cp_i] = '\0';
	return (redir);
}

int	parse_redir(char *str, t_command **command, int *i, int *redir_pos)
{
	(*command)->redir[*redir_pos] = create_redir(str + (*i));
	if (!((*command)->redir[(*redir_pos)++]))
		return (PARSING);
	while (is_redir(str, (*i)))
		++(*i);
	while (ft_isspace(str[(*i)]))
		++(*i);
	while (str[(*i)] > ' ' && !is_redir(str, (*i)))
		++(*i);
	return (FN_SUCCESS);
}
