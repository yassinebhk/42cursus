/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:44:14 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/21 23:11:09 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_char(char c, int index)
{
	if (c == '=' && index != 0)
		return (1);
	else if (ft_isalpha(c))
		return (1);
	else if (ft_isdigit(c) && index != 0)
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

static int	valid_var(char *var)
{
	int		j;

	j = -1;
	while (var[++j])
	{
		if (!(valid_char(var[j], j)))
			return (1);
	}
	return (0);
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
	return (rmv);
}

static int	set_var_and_value(char *str, t_env *exp, t_env *env)
{
	char	**split;

	split = ft_split_mod(str, '=');
	if (valid_var(split[0]))
		return (BAD_ASSIGNMENT);
	ft_add_back(&exp, ft_new_node(split[0], split[1], EXPORT_FLAG));
	ft_add_back(&env, ft_new_node(split[0], split[1], ENV_FLAG));
	ft_free(split);
	return (0);
}

static int	set_var(char *str, t_env *exp, t_env *env, int flag)
{
	if (!flag)
	{
		if (valid_var(str))
			return (BAD_ASSIGNMENT);
		ft_add_back(&exp, ft_new_node(str, NULL, EXPORT_FLAG));
	}
	else if (flag == 1)
	{
		if (valid_var(str))
			return (BAD_ASSIGNMENT);
		str = rm_eq(str);
		if (!str)
			return (ENO_MEM);
		ft_add_back(&exp, ft_new_node(str, "", EXPORT_FLAG));
		ft_add_back(&env, ft_new_node(str, "", ENV_FLAG));
		free(str);
	}
	else
		return (set_var_and_value(str, exp, env));
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
		while (++pos < num_words && !result)
		{
			if (!exist_var(str[pos], env, exp))
				result = 0;
			else if (!find_eq(str[pos]))
				result = set_var(str[pos], exp, env, 0);
			else if (find_eq(str[pos]) == 1)
				result = set_var(str[pos], exp, env, 1);
			else
				result = set_var(str[pos], exp, env, 2);
		}
	}
	return (result);
}
