/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:52:41 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/19 16:50:32 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_var(char **split, t_env *env, int flag)
{
	while (env)
	{
		if (!ft_strcmp(env->key, split[0]) && !flag)
			env->var = ft_strdup(split[1]);
		else if (!ft_strcmp(env->key, ft_strjoin("declare -x ",
					ft_strdup(split[0]))))
			env->var = ft_strjoin("\"", ft_strjoin(ft_strdup(split[1]), "\""));
		env = env->next;
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

static int	set_var_two(char *str, t_env *env, int flag)
{
	t_env	*new_node;
	char	**split;

	if (!find_eq(str))
	{
		new_node = ft_new_node(str, NULL, 1);
		ft_add_back(&env, new_node);
	}
	else if (find_eq(str) == 1)
	{
		str = rm_eq(str);
		new_node = ft_new_node(str, "", flag);
		ft_add_back(&env, new_node);
	}
	else
	{
		split = ft_split_mod(str, '=');
		new_node = ft_new_node(split[0], split[1], flag);
		ft_add_back(&env, new_node);
		ft_free(split);
	}
	return (0);
}

int	exist_var(char *str, t_env *env, t_env *exp)
{
	int		var;
	char	**split;

	split = ft_split_mod(str, '=');
	var = find_var(split[0], env, exp);
	if (!var)
		return (1);
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
