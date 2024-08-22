/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:44:14 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/22 13:40:01 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (rmv);
}

static void	set_var_and_value(char *str, t_env *exp, t_env *env)
{
	char	**split;

	split = ft_split_mod(str, '=');
	ft_add_back(&exp, ft_new_node(split[0], split[1], EXPORT_FLAG));
	ft_add_back(&env, ft_new_node(split[0], split[1], ENV_FLAG));
	ft_free(split);
}

static int	set_var(char *str, t_env *exp, t_env *env, int flag)
{
	if (!flag)
		ft_add_back(&exp, ft_new_node(str, NULL, EXPORT_FLAG));
	else if (flag == 1)
	{
		str = rm_eq(str);
		if (!str)
			return (1);
		ft_add_back(&exp, ft_new_node(str, "", EXPORT_FLAG));
		ft_add_back(&env, ft_new_node(str, "", ENV_FLAG));
		free(str);
	}
	else
		set_var_and_value(str, exp, env);
	return (0);
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
