/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:10:15 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 21:23:32 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exist_var(char *str, t_env *env, t_env *exp)
{
	while (env)
	{
		if (!ft_strcmp(env->key, str) || !ft_strcmp(ft_strjoin(str, "="), str))
			return (1);
		env = env->next;
	}
	while (exp)
	{
		if (!ft_strcmp(exp->key, ft_strjoin("declare -x ", str))
			|| !ft_strcmp(ft_strjoin("declare -x ", ft_strjoin(str, "=")), str))
			return (2);
		exp = exp->next;
	}
	return (0);
}

void	delete_var(char *str, t_env **env, t_env **exp, int flag)
{
	t_env	*tmp;

	if (!flag)
	{
		while (ft_strcmp((*env)->next->key, str) || ft_strcmp(ft_strjoin(str,
					"="), str))
			(*env) = (*env)->next;
		tmp = (*env)->next;
		(*env)->next = (*env)->next->next;
		free(tmp);
	}
	while (ft_strcmp((*exp)->next->key, ft_strjoin("declare -x ", str))
		|| ft_strcmp(ft_strjoin("declare -x ", ft_strjoin(str, "=")), str))
		(*exp) = (*exp)->next;
	tmp = (*exp)->next;
	(*exp)->next = (*exp)->next->next;
	free(tmp);
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
			if (exist_var(str[pos], env, exp) == 1)
				delete_var(str[pos], &env, &exp, 0);
			else if (exist_var(str[pos], env, exp) == 2)
				delete_var(str[pos], &env, &exp, 1);
		}
	}
	return (result);
}

No funciona para el caso z=