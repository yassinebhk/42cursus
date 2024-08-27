#include "minishell.h"

void	ft_free(char **str)
{
	int	i;

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

static void	free_content(t_command *command)
{
	int	pos;

	if (!command)
		return ;
	free(command->command);
	if (command->num_redir > 0 && command->redir)
	{
		pos = -1;
		while (++pos < command->num_redir)
			free(command->redir[pos].filename);
		free(command->redir);
	}
	if (command->num_args > 0 && command->args)
	{
		pos = -1;
		while (++pos < command->num_args)
			free(command->args[pos]);
		free(command->args);
	}
}

void	free_list(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head->next;
		free_args(head->var_list.env, head->var_list.exp);
		free_content(head->content);
		free(head->content);
		free(head);
		head = tmp;
	}
}
