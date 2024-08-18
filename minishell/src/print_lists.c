/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:32:17 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/18 18:53:29 by ybouhaik         ###   ########.fr       */
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

int	ft_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->var);
		env = env->next;
	}
	return (0);
}