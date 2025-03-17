/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:24:40 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/03/14 14:03:06 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_env(char **environment)
{
	int	len;

	len = 0;
	while (environment[len])
		len++;
	return (len);
}

int	find_node(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (0);
		env = env->next;
	}
	return (1);
}

static t_node	*ft_last_node(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_node_back(t_node **head, t_node *new_node)
{
	t_node	*last;

	if (!new_node)
	{
		perror(ENO_MEM_ERROR);
		return ;
	}
	if (!*head)
		*head = new_node;
	else
	{
		last = ft_last_node(*head);
		if (last)
			last->next = new_node;
	}
}

int	ft_len_node(t_node *head)
{
	int		size;
	t_node	*tmp;

	size = 0;
	tmp = head;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}
