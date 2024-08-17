/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:16:58 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 15:50:22 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_built(char **str, int num_words, t_env *env)
{
	if (!ft_strcmp(str[0], "echo"))
		return (echo(str, 0, num_words));
	else if (!ft_strcmp(str[0], "cd"))
		return (cd(str, 0, num_words, env));
	// else if (!ft_strcmp(str[0], "pwd"))
	// 	return (pwd(str, 0, lst_size, env));
	// else if (!ft_strcmp(str[0], "export"))
	// 	return (export(str[0], 0));
	// else if (!ft_strcmp(str[0], "unset"))
	// 	return (unset(str[0], 0));
	// else if (!ft_strcmp(str[0], "env"))
	// 	return (ft_env(str[0], 0));
	// else if (!ft_strcmp(str[0], "exit"))
	// 	return (ft_exit(str[0], 0));
	return (0);
}
