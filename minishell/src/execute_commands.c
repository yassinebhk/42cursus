/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:05:56 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/05/02 16:13:04 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe function failed");
		return (FN_FAILURE);
	}
	return (FN_SUCCESS);
}

static int	handle_fork(t_node **nodes, t_lists *lists, int fd[2],
							int prev_fd_in)
{
	t_node	*tmp;
	t_node	*head;
	int		pid;
	int		status;

	tmp = nodes[0];
	head = nodes[1];
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return (FN_FAILURE);
	}
	if (pid == 0)
	{
		if (prev_fd_in != -1)
			close(fd[0]);
		execute_child(lists, (t_node *[]){head, tmp}, fd, prev_fd_in);
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
