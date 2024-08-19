/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:44:14 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/19 16:38:15 by ybouhaik         ###   ########.fr       */
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
	free(str);
	return (rmv);
}

static int	set_var(char *str, t_env *exp, t_env *env, int flag)
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
