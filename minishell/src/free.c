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
