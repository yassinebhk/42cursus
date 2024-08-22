#include "minishell.h"

static void	set(t_env **list, char *curr, char *old, int list_type)
{
	t_env	*curr_dir;

	if (!list_type)
	{
		curr_dir = ft_new_node("PWD\0", curr, 0);
		if (!curr_dir)
		{
			free(curr);
			free(old);
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		curr_dir = ft_new_node("PWD\0", curr, EXPORT_FLAG);
		if (!curr_dir)
		{
			free(curr);
			free(old);
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
	}
	ft_add_back(list, curr_dir);
}

void	set_dirs_env(t_env **env, char *curr, char *old)
{
	t_env	*old_dir;

	if (find_node(*env, "PWD\0"))
		set(env, curr, old, 0);
	else if (find_node(*env, "OLDPWD\0"))
	{
		old_dir = ft_new_node("OLDPWD\0", old, 0);
		if (!old_dir)
		{
			free(curr);
			free(old);
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		ft_add_back(env, old_dir);
	}
	free(curr);
	free(old);
}

void	set_dirs_exp(t_env **exp, char *curr, char *old)
{
	t_env	*old_dir;

	if (find_node(*exp, "declare -x PWD\0"))
		set(exp, curr, old, 1);
	else if (find_node(*exp, "declare -x OLDPWD\0"))
	{
		old_dir = ft_new_node("declare -x OLDPWD\0", old, 0);
		if (!old_dir)
		{
			free(curr);
			free(old);
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		ft_add_back(exp, old_dir);
	}
	free(curr);
	free(old);
}

t_env	*get_var(char **environment, int flag)
{
	int		pos;
	t_env	*env;
	char	**split;
	t_env	*new_node;

	pos = -1;
	env = NULL;
	while (++pos < len_env(environment))
	{
		split = ft_split_mod(environment[pos], '=');
		new_node = ft_new_node(split[0], split[1], flag);
		new_node->index = -1;
		ft_add_back(&env, new_node);
		ft_free(split);
	}
	if (!flag)
		set_dirs_env(&env, getcwd(NULL, 0), getcwd(NULL, 0));
	else
		set_dirs_exp(&env, getcwd(NULL, 0), getcwd(NULL, 0));
	return (env);
}
