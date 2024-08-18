/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:32:17 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/18 16:48:03 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->var);
		env = env->next;
	}
	return (0);
}