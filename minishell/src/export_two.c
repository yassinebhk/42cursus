#include "minishell.h"

static void	update_var(char **split, t_env **env, int flag)
{
	char	*tmp;
	t_env	*aux;

	aux = *env;
	while (aux)
	{
		tmp = ft_strjoin("declare -x ", split[0]);
		if (!ft_strcmp(aux->key, split[0]) && !flag)
		{
			free(aux->var);
			aux->var = ft_strdup(split[1]);
		}
		else if (!ft_strcmp(aux->key, tmp))
		{
			free(tmp);
			tmp = ft_strjoin(split[1], "\"");
			free(aux->var);
			aux->var = ft_strjoin("\"", tmp);
		}
		free(tmp);
		aux = aux->next;
	}
}

static int	find_var(char *str, t_env *env, t_env *exp)
{
	int		flag;
	char	*tmp;

	flag = 0;
	while (env)
	{
		if (!ft_strcmp(env->key, str))
			flag = 1;
		env = env->next;
	}
	while (exp)
	{
		tmp = ft_strjoin("declare -x ", str);
		if (!ft_strcmp(exp->key, tmp))
		{
			if (!flag)
				flag = 2;
			else
				flag = 3;
		}
		exp = exp->next;
		free(tmp);
	}
	return (flag);
}

static int	set_var_two(char *str, t_env **env, int flag)
{
	t_env	*new_node;
	char	**split;

	if (!find_eq(str))
	{
		new_node = ft_new_node(str, NULL, 1);
		ft_add_back(env, new_node);
	}
	else if (find_eq(str) == 1)
	{
		str = rm_eq(str);
		new_node = ft_new_node(str, "", flag);
		ft_add_back(env, new_node);
		free(str);
	}
	else
	{
		split = ft_split_mod(str, '=');
		new_node = ft_new_node(split[0], split[1], flag);
		ft_add_back(env, new_node);
		ft_free(split);
	}
	return (0);
}

int	exist_var(char *str, t_env **env, t_env **exp)
{
	int		var;
	char	**split;

	split = ft_split_mod(str, '=');
	var = find_var(split[0], *env, *exp);
	if (!var)
		return (ft_free(split), 1);
	else if (var == 1)
	{
		if (split[1])
			update_var(split, env, 0);
		set_var_two(str, exp, 1);
	}
	else if (var == 2)
	{
		if (split[1])
			update_var(split, exp, 1);
		set_var_two(str, env, 0);
	}
	else if (var == 3 && split[1])
	{
		update_var(split, exp, 1);
		update_var(split, env, 0);
	}
	return (ft_free(split), 0);
}
