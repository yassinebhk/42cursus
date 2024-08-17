/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:44:14 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 21:23:17 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_list(t_env *env)
{
	while (env)
	{
		if (!env->var)
			printf("%s\n", env->key);
		else if (!ft_strcmp(env->var, "\"\""))
			printf("%s%s\n", env->key, env->var);
		else
			printf("%s=%s\n", env->key, env->var);
		env = env->next;
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

int	set_var(char *str, t_env *exp, t_env *env, int flag)
{
	t_env	*new_node;
	char	**split;

	if (!flag)
	{
		new_node = ft_new_node(str, NULL, 1);
		ft_add_back(&exp, new_node);
	}
	else if (flag == 1)
	{
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

Caso en el que sobreescriba un vable
// Hacer unset en el caso de que:
// z -> z""
// z"" -> z"3"
// z"3" -> z""


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
			//if (exist_var(str[pos]))
			if (!find_eq(str[pos]) && !set_var(str[pos], exp, env, 0))
				result = 1;
			else if (find_eq(str[pos]) == 1 && !set_var(str[pos], exp, env, 1))
				result = 1;
			else if (!set_var(str[pos], exp, env, 2))
				result = 1;
		}
	}
	return (result);
}
