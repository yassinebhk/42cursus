/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:34:43 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/02/09 16:46:47 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_var(char *str, t_env *env, t_env *exp)
{
	char	*tmp;

	if (!str)
		return (0);
	while (env)
	{
		if (!ft_strcmp(env->key, str))
			return (1);
		env = env->next;
	}
	while (exp)
	{
		tmp = ft_strjoin("declare -x ", str);
		if (!ft_strcmp(exp->key, tmp))
			return (free(tmp), 2);
		exp = exp->next;
		free(tmp);
	}
	return (0);
}

static void	delete(char *key, t_env **lists)
{
	t_env	tmp;
	t_env	*aux;
	t_env	*curr;

	tmp.next = *lists;
	curr = &tmp;
	while (curr->next)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			free(curr->next->key);
			free(curr->next->var);
			aux = curr->next->next;
			free(curr->next);
			curr->next = aux;
			break ;
		}
		curr = curr->next;
	}
	*lists = tmp.next;
}

void	delete_var(char *str, t_env **env, t_env **exp, int flag)
{
	char	*key;

	if (!flag)
		delete (str, env);
	key = ft_strjoin("declare -x ", str);
	delete (key, exp);
	free(key);
}

char	*add_eq(char *str)
{
	int		pos;
	char	*rmv;

	pos = -1;
	rmv = (char *)malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!rmv)
		return (NULL);
	while (++pos < ((int)ft_strlen(str)))
		rmv[pos] = str[pos];
	rmv[pos] = '=';
	rmv[pos + 1] = '\0';
	free(str);
	return (rmv);
}

int	unset(char **args, int num_args, t_lists **lists)
{
	int	pos;

	pos = 0;
	if (num_args > 1)
	{
		while (++pos < num_args)
		{
			if (check_var(args[pos], (*lists)->env, (*lists)->exp) == 1)
				delete_var(args[pos], &(*lists)->env, &(*lists)->exp, 0);
			else if (check_var(args[pos], (*lists)->env, (*lists)->exp) == 2)
				delete_var(args[pos], &(*lists)->env, &(*lists)->exp, 1);
		}
	}
	return (0);
}
