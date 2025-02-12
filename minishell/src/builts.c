/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:29:00 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/02/09 16:56:39 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_built(t_node **head, t_lists **lists)
{
	int		num_args;
	char	**args;

	num_args = (*head)->content->num_args;
	args = (*head)->content->args;
	if (!ft_strcmp(args[0], "echo"))
		return (echo(args, num_args));
	else if (!ft_strcmp(args[0], "cd"))
		return (cd(args, num_args, lists));
	else if (!ft_strcmp(args[0], "pwd"))
		return (pwd((*lists)->env));
	else if (!ft_strcmp(args[0], "export"))
		return (export(args, num_args, lists));
	else if (!ft_strcmp(args[0], "unset"))
		return (unset(args, num_args, lists));
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env((*lists)->env));
	else
		return (ft_exit(args, &(*lists)->env, &(*lists)->exp, head));
	return (FN_SUCCESS);
}
