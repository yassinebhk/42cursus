/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:21:51 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/04/27 13:02:26 by maxgarci         ###   ########.fr       */
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

void	free_lists(t_env *env, t_env *exp)
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

static void	free_command(t_command *command)
{
	if (!command)
		return ;
	free(command->command);
	command->command = NULL;
}

void	free_content(t_command *command)
{
	int	pos;

	free_command(command);
	if (command->args)
	{
		pos = -1;
		while (++pos <= command->num_args && command->args[pos])
		{
			free(command->args[pos]);
			command->args[pos] = NULL;
		}
		free(command->args);
		command->args = NULL;
	}
	if (command->num_redir > 0 && command->redir)
	{
		pos = -1;
		while (++pos < command->num_redir && command->redir[pos])
		{
			free(command->redir[pos]->filename);
			free(command->redir[pos]);
		}
		free(command->redir);
		command->redir = NULL;
	}
}

void	free_node(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->var_list)
		{
			free_lists(head->var_list->env, head->var_list->exp);
			free(head->var_list);
			head->var_list = NULL;
		}
		if (head->content)
		{
			free_content(head->content);
			free(head->content);
			head->content = NULL;
		}
		free(head);
		head = tmp;
	}
	head = NULL;
}
