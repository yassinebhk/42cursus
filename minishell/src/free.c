/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:14:05 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 17:26:40 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_args(char *line, t_env *env, t_env *exp)
{
	free(line);
	while (env)
	{
		free(env->key);
		if (env->var)
			free(env->var);
		env = env->next;
	}
	free(env);
	while (exp)
	{
		free(exp->key);
		if (exp->var)
			free(exp->var);
		exp = exp->next;
	}
	free(exp);
}
