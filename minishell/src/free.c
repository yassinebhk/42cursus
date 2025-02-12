/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:21:51 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/02/09 13:11:06 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free(char **str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	free_args(t_env *env, t_env *exp)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		if (env->var)
			free(env->var);
		free(env);
		env = tmp;
	}
	while (exp)
	{
		tmp = exp->next;
		free(exp->key);
		if (exp->var)
			free(exp->var);
		free(exp);
		exp = tmp;
	}
}

void	free_content(t_command *command)
{
	int	pos;

	if (!command)
		return ;
	if (command->num_args > 0 && command->args)
	{
		pos = -1;
		while (++pos < command->num_args)
			free(command->args[pos]);
		free(command->args);
	}
	if (command->num_redir > 0 && command->redir)
	{
		pos = -1;
		while (++pos < command->num_redir)
			free(command->redir[pos].filename);
		free(command->redir);
	}
}

void	free_list(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head->next;
		free_args(head->var_list->env, head->var_list->exp);
		free(head->var_list);
		free_content(head->content);
		free(head->content);
		free(head);
		head = tmp;
	}
}
