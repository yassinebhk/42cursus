/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:16:58 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 20:10:56 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_built(char **str, int num_words, t_env *env, t_env *exp)
{
	if (!ft_strcmp(str[0], "echo"))
		return (echo(str, 0, num_words));
	else if (!ft_strcmp(str[0], "cd"))
		return (cd(str, num_words, env, exp));
	else if (!ft_strcmp(str[0], "pwd"))
		return (pwd(env));
	else if (!ft_strcmp(str[0], "export"))
		return (export(str, num_words, env, exp));
	else if (!ft_strcmp(str[0], "unset"))
		return (unset(str, num_words, env, exp));
	// else if (!ft_strcmp(str[0], "env"))
	// 	return (ft_env(str[0], 0));
	// else if (!ft_strcmp(str[0], "exit"))
	// 	return (ft_exit(str[0], 0));
	return (0);
}
