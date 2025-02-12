/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:45:02 by maxgarci          #+#    #+#             */
/*   Updated: 2025/02/09 17:05:22 by maxgarci         ###   ########.fr       */
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
	//str = get_trunc_str(line, init_pos, end_pos);
	str = (char *)ft_calloc(1, sizeof(char)*(end_pos - init_pos));
	size = ft_strlcpy(str, line + init_pos, end_pos - init_pos);
	if (!size)
		return (free(command), NULL);
	if (new_command(str, &command))
		return (free(str), free(command), NULL);
	return (free(str), command);
}

static t_env	*ft_nodedup(t_env *node)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (perror(ENO_MEM_ERROR), NULL);
	new_node->index = node->index;
	new_node->key = ft_strdup(node->key);
	new_node->next = NULL;
	if (node->var)
		new_node->var = ft_strdup(node->var);
	else
		new_node->var = NULL;
	return (new_node);
}

static t_env	*ft_listdup(t_env *list)
{
	t_env	*new_env;
	t_env	*tmp;
	t_env	*curr;

	if (!list)
		return (NULL);
	new_env = ft_nodedup(list);
	if (!new_env)
		return (NULL);
	
	tmp = new_env;
	list = list->next;
	while (list)
	{
		curr = ft_nodedup(list);
		if (!curr)
			return (NULL);
		tmp->next = curr;
		tmp = tmp->next;
		list = list->next;
	}
	return (new_env);
}


static t_node	*fill_node(char *line, int *pos, t_lists *lists, int status)
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
	new_node->status = status;
	new_node->fd_in = 0;
	new_node->fd_out = 1;
	new_node->next = NULL;
	new_node->content = get_content(line, init_pos, *pos);
	if (!new_node->content)
		return (free_args(new_node->var_list->env, new_node->var_list->exp),
			free(new_node->var_list), free(new_node),
			perror(ENO_MEM_ERROR), NULL);
	return (new_node);
}

int	fill_nodes(char *line, t_node **head, t_lists *lists, int status)
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
		new_node = fill_node(line, &pos, lists, status);
		if (!new_node)
			return (free_list(*head), *head = NULL, 1);
		ft_add_node_back(head, new_node);
	}
	return (0);
}
