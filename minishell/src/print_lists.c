/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:52:10 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/02/09 16:52:32 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*set_index(t_env *exp)
{
	t_env	*current;
	t_env	*tmp;

	current = exp;
	while (current)
	{
		current->index = 0;
		tmp = exp;
		while (tmp)
		{
			if (ft_strcmp(current->key, tmp->key) > 0)
				current->index++;
			tmp = tmp->next;
		}
		current = current->next;
	}
	return (exp);
}

static t_env	*get_node_index(int index, t_env *exp)
{
	t_env	*current;

	current = exp;
	while (current)
	{
		if (current->index == index)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	print_export_list(t_env *exp)
{
	int		index;
	t_env	*tmp;

	index = -1;
	exp = set_index(exp);
	while (++index < ft_lst_size(exp))
	{
		tmp = get_node_index(index, exp);
		if (tmp && !tmp->var)
			printf("%s\n", tmp->key);
		else
			printf("%s=%s\n", tmp->key, tmp->var);
	}
}

int	ft_env(t_env *env)
{
	while (env)
	{
		ft_putstr2_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr2_fd(env->var, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
	return (0);
}
