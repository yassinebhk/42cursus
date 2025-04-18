/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:29:00 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/04/16 10:23:35 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	dup_file_descriptors(t_node **head)
{
	if ((*head)->fd_in != STDIN_FILENO && (*head)->fd_in != -1)
	{
		if (dup2((*head)->fd_in, STDIN_FILENO) == -1)
			return (perror("dup2 fd_in failed"), 1);
		close((*head)->fd_in);
	}
	if ((*head)->fd_out != STDOUT_FILENO && (*head)->fd_out != -1)
	{
		if (dup2((*head)->fd_out, STDOUT_FILENO) == -1)
			return (perror("dup2 fd_out failed"), 1);
		close((*head)->fd_out);
	}
	return (0);
}

int	execute_built(t_node **head, t_lists *lists)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (perror("Error saving original fd"), 1);
	if (set_fd(head))
		return (FN_FAILURE);
	dup_file_descriptors(head);
	(*head)->last_status = find_built(head, &lists);
	if (dup2(saved_stdin, STDIN_FILENO) == -1 || dup2(saved_stdout,
			STDOUT_FILENO) == -1)
		return (perror("Error restoring original fd"), 1);
	close(saved_stdin);
	close(saved_stdout);
	return ((*head)->last_status);
}

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
