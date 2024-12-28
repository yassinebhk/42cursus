#include "minishell.h"

static int	set_var_and_value(char *str, t_env **exp, t_env **env)
{
	char	**split;

	split = ft_split_mod(str, '=');
	if (valid_var(split[0]))
			return (ft_free(split), ft_putstr_fd(" not a valid identifier\n", 2), BAD_ASSIGNMENT);
	ft_add_back(exp, ft_new_node(split[0], split[1], EXPORT_FLAG));
	ft_add_back(env, ft_new_node(split[0], split[1], ENV_FLAG));
	return (ft_free(split), 0);
}

static int	set_var(char *str, t_env **exp, t_env **env, int flag)
{
	if (!flag)
	{
if (valid_var(str))
			return (ft_putstr_fd(" not a valid identifier\n", 2), BAD_ASSIGNMENT);
		ft_add_back(exp, ft_new_node(str, NULL, EXPORT_FLAG));
	}
	else if (flag == 1)
	{
		if (valid_var(str))
			return (ft_putstr_fd(" not a valid identifier\n", 2), BAD_ASSIGNMENT);
		str = rm_eq(str);
		if (!str)
			return (ENO_MEM);
		ft_add_back(exp, ft_new_node(str, NULL, EXPORT_FLAG));
		ft_add_back(env, ft_new_node(str, NULL, ENV_FLAG));
		free(str);
	}
	else
		return (set_var_and_value(str, exp, env));
	return (0);
}

int	export(char **str, int num_words, t_lists **list, t_node **head)
{
	int	pos;
	int	result;

	pos = 0;
	result = 0;
	if (num_words == 1)
		print_export_list((*list)->exp);
	else
	{
		while (++pos < num_words && !result)
		{
			if (!exist_var(str[pos], &(*list)->env, &(*list)->exp))
				(result) = 0;
			else if (!find_eq(str[pos]))
				(result) = set_var(str[pos], &(*list)->exp, &(*list)->env, 0);
			else if (find_eq(str[pos]) == 1)
				(result) = set_var(str[pos], &(*list)->exp, &(*list)->env, 1);
			else
				(result) = set_var(str[pos], &(*list)->exp, &(*list)->env, 2);
		}
	}
	(*head)->error = result;
	return ((result));
}
