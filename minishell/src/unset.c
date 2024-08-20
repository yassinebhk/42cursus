/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:10:15 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/20 15:36:12 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var(char *str, t_env *env, t_env *exp)
{
	char	*tmp;

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

static void	delete(char *key, t_env **list)
{
	t_env	tmp;
	t_env	*aux;
	t_env	*curr;

	tmp.next = *list;
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
	*list = tmp.next;
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

int	unset(char **str, int num_words, t_env *env, t_env *exp)
{
	int	pos;
	int	result;

	result = 0;
	pos = 0;
	if (num_words > 1)
	{
		while (++pos < num_words)
		{
			if (check_var(str[pos], env, exp) == 1)
				delete_var(str[pos], &env, &exp, 0);
			else if (check_var(str[pos], env, exp) == 2)
				delete_var(str[pos], &env, &exp, 1);
		}
	}
	return (result);
}
