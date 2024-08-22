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
