#include "minishell.h"

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
		if (!tmp->var)
			printf("%s\n", tmp->key);
		else
			printf("%s=%s\n", tmp->key, tmp->var);
	}
}

int	ft_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->var);
		env = env->next;
	}
	return (0);
}
