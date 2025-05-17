/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:05:56 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/05/18 10:18:22 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("pipe function failed", 2);
		return (FN_FAILURE);
	}
	return (FN_SUCCESS);
}

static int	handle_fork(t_node **nodes, t_lists *lists, int fd[2],
		int prev_fd_in)
{
	int		pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork failed", 2);
		return (FN_FAILURE);
	}
	if (pid == 0)
	{
		if (prev_fd_in != -1)
			close(fd[0]);
		execute_child(lists, (t_node *[]){nodes[1], nodes[0]}, fd, prev_fd_in);
	}
	else
	{
		close(fd[1]);
		wait(&status);
	}
	return (status);
}

int	execute_commands(t_node **head, t_lists *lists)
{
	int		fd[2];
	int		prev_fd_in;
	int		status;
	t_node	*tmp;

	if (set_fd(head))
		return (EXIT_FAILURE);
	tmp = *head;
	status = FN_SUCCESS;
	prev_fd_in = tmp->fd_in;
	while (tmp)
	{
		if (handle_pipe(fd) == FN_SUCCESS)
			status = handle_fork((t_node *[]){tmp, *head}, lists, fd,
					prev_fd_in);
		if (prev_fd_in)
			close(prev_fd_in);
		prev_fd_in = dup(fd[0]);
		close(fd[0]);
		tmp = tmp->next;
	}
	if (prev_fd_in != -1)
		close(prev_fd_in);
	return (status);
}
