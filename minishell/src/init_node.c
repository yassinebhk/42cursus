/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:45:02 by maxgarci          #+#    #+#             */
/*   Updated: 2025/04/20 13:01:18 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_command	*get_content(char *line, int init_pos, int end_pos)
{
	char		*str;
	size_t		size;
	t_command	*command;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!command)
		return (perror(ENO_MEM_ERROR), NULL);
	str = (char *)ft_calloc(1, sizeof(char) * (end_pos - init_pos));
	size = ft_strlcpy(str, line + init_pos, end_pos - init_pos);
	if (!size)
		return (free(command), NULL);
	if (new_command(str, &command))
		return (free(str), free_content(command), free(command), NULL);
	return (free(str), command);
}

static void	find_pipe(char *line, int *pos)
{
	int	single_quote_open;
	int	double_quote_open;

	single_quote_open = 0;
	double_quote_open = 0;
	if (line == NULL)
		return ;
	while (line[*pos])
	{
		if (line[*pos] == SINGLE_QUOTE && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (line[*pos] == DOUBLE_QUOTE && !single_quote_open)
			double_quote_open = !double_quote_open;
		else if (line[*pos] == PIPE && !single_quote_open && !double_quote_open)
		{
			if (*pos == 0 || (line[*pos - 1] != BACKSLASH))
				break ;
		}
		(*pos)++;
	}
	(*pos)++;
}

static t_node	*fill_node(char *line, int *pos, t_lists *lists,
		int last_status)
{
	int		init_pos;
	t_node	*new_node;

	init_pos = *pos;
	find_pipe(line, pos);
	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (perror(ENO_MEM_ERROR), NULL);
	new_node->var_list = (t_lists *)ft_calloc(1, sizeof(t_lists));
	if (!new_node->var_list)
		return (free(new_node), perror(ENO_MEM_ERROR), NULL);
	new_node->var_list->env = ft_listdup(lists->env);
	new_node->var_list->exp = ft_listdup(lists->exp);
	new_node->last_status = last_status;
	new_node->fd_in = STDIN_FILENO;
	new_node->fd_out = STDOUT_FILENO;
	new_node->next = NULL;
	new_node->content = get_content(line, init_pos, *pos);
	if (!new_node->content)
		return (free_lists(new_node->var_list->env, new_node->var_list->exp),
			free(new_node->var_list), free(new_node), perror(ENO_MEM_ERROR),
			NULL);
	return (new_node);
}

int	fill_nodes(char *line, t_node **head, t_lists *lists, int last_status)
{
	int		i;
	int		pos;
	int		npipes;
	t_node	*new_node;

	i = -1;
	pos = 0;
	npipes = count_pipes(line);
	while (++i <= npipes)
	{
		new_node = fill_node(line, &pos, lists, last_status);
		if (!new_node)
			return (FN_FAILURE);
		if (!i)
			*head = new_node;
		else
			ft_add_node_back(head, new_node);
	}
	return (FN_SUCCESS);
}
