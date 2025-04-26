/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:05:56 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/04/20 19:51:31 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_commands(t_node **head, t_lists *lists)
{
	int		pid;
	int		fd[2];
	int		prev_fd_in;
	int		status;
	t_node	*tmp;

	if (set_fd(head))
		return (EXIT_FAILURE);
	tmp = *head;
	prev_fd_in = tmp->fd_in;
	while (tmp)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe function failed");
			return (FN_FAILURE);
		}
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
			execute_child(lists, (t_node *[]){(*head), tmp}, fd, prev_fd_in);
		}
		else
		{
			close(fd[1]);
			wait(&status);
		}
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
