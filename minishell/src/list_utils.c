/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:29:16 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 14:29:38 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
	{
		printf("Error: new node is NULL\n");
		return ;
	}
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_last(*lst);
		if (last)
			last->next = new;
	}
}

t_env	*ft_new_node(char *key, char *arg)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	node->next = NULL;
	node->key = ft_strdup(key);
	if (!arg)
		node->var = NULL;
	else
		node->var = ft_strdup(arg);
	return (node);
}

int	ft_lst_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		env = env->next;
		size++;
	}
	return (size);
}