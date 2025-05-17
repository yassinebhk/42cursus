/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:17:20 by maxgarci          #+#    #+#             */
/*   Updated: 2025/05/13 20:42:46 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_nodedup(t_env *node)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (ft_putstr_fd(ENO_MEM_ERROR, 2), NULL);
	new_node->index = node->index;
	new_node->key = ft_strdup(node->key);
	new_node->next = NULL;
	if (node->var)
		new_node->var = ft_strdup(node->var);
	else
		new_node->var = NULL;
	return (new_node);
}

t_env	*ft_listdup(t_env *list)
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
