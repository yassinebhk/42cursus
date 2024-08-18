/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:44:14 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/18 18:50:34 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_list(t_env *exp)
{
	while (exp)
	{
		if (!exp->var)
			printf("%s\n", exp->key);
		else
			printf("%s=%s\n", exp->key, exp->var);
		exp = exp->next;
	}
}

int	find_eq(char *str)
{
	int	pos;
	int	flag;
	int	cont;

	pos = -1;
	flag = 0;
	cont = 0;
	while (str[++pos])
	{
		if (str[pos] == '=')
			flag++;
		if (flag)
			cont++;
	}
	return (cont);
}

char	*rm_eq(char *str)
{
	int		pos;
	char	*rmv;

	pos = -1;
	rmv = (char *)malloc((ft_strlen(str)) * sizeof(char));
	if (!rmv)
		return (NULL);
	while (++pos < ((int)ft_strlen(str)) - 1)
		rmv[pos] = str[pos];
	rmv[pos] = '\0';
	free(str);
	return (rmv);
}

int	set_var(char *str, t_env *exp, t_env *env, int flag)
{
	t_env	*new_node;
	char	**split;

	if (!flag)
		ft_add_back(&exp, ft_new_node(str, NULL, 1));
	else if (flag == 1)
	{
		str = rm_eq(str);
		new_node = ft_new_node(str, "", 1);
		ft_add_back(&exp, new_node);
		new_node = ft_new_node(str, "", 0);
		ft_add_back(&env, new_node);
	}
	else
	{
		split = ft_split_mod(str, '=');
		new_node = ft_new_node(split[0], split[1], 1);
		ft_add_back(&exp, new_node);
		new_node = ft_new_node(split[0], split[1], 0);
		ft_add_back(&env, new_node);
		ft_free(split);
	}
	return (0);
}

void	update_var(char **split, t_env *env, int flag)
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

int	find_var(char *str, t_env *env, t_env *exp)
{
	int	flag;

	flag = 0;
	while (env)
	{
		if (!ft_strcmp(env->key, str))
			flag = 1;
		env = env->next;
	}
	while (exp)
	{
		if (!ft_strcmp(exp->key, ft_strjoin("declare -x ", str)))
		{
			if (!flag)
				flag = 2;
			else
				flag = 3;
		}
		exp = exp->next;
	}
	return (flag);
}

int	set_var_two(char *str, t_env *env, int flag)
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

int	export(char **str, int num_words, t_env *env, t_env *exp)
{
	int	pos;
	int	result;

	pos = 0;
	result = 0;
	if (num_words == 1)
		print_export_list(exp);
	else
	{
		while (++pos < num_words)
		{
			if (!exist_var(str[pos], env, exp))
				result = 1;
			else if (!find_eq(str[pos]) && !set_var(str[pos], exp, env, 0))
				result = 1;
			else if (find_eq(str[pos]) == 1 && !set_var(str[pos], exp, env, 1))
				result = 1;
			else if (!set_var(str[pos], exp, env, 2))
				result = 1;
		}
	}
	return (result);
}
