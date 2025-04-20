/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:05:56 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/04/20 13:08:22 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_command_execution(t_node *head, t_node *tmp, t_lists *lists,
		int prev_fd_in)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
		return (perror("pipe function failed"), FN_FAILURE);
	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), FN_FAILURE);
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
	return (dup(fd[0]));
}

static int	loop_through_commands(t_node *head, t_lists *lists)
{
	t_node	*tmp;
	int		prev_fd_in;
	int		new_fd;
	int		status;

	tmp = head;
	prev_fd_in = tmp->fd_in;
	status = 0;
	while (tmp)
	{
		new_fd = handle_command_execution(head, tmp, lists, prev_fd_in);
		if (new_fd == FN_FAILURE)
			return (FN_FAILURE);
		if (prev_fd_in != -1)
			close(prev_fd_in);
		prev_fd_in = new_fd;
		tmp = tmp->next;
	}
	if (prev_fd_in != -1)
		close(prev_fd_in);
	return (status);
}

int	execute_commands(t_node **head, t_lists *lists)
{
	if (set_fd(head))
		return (EXIT_FAILURE);
	return (loop_through_commands(*head, lists));
}
