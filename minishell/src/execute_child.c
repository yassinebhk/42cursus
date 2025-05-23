/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 09:41:31 by maxgarci          #+#    #+#             */
/*   Updated: 2025/05/13 20:46:26 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exit_child(char *str, t_node *head, t_lists *lists, int fd)
{
	if (str)
		ft_putstr_fd(str, 2);
	free_node(head);
	free_lists(lists->env, lists->exp);
	if (fd != -1)
		close(fd);
	if (!str)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

static void	redirect_fds(t_lists *lists, t_node **nodes, int *fd, int *prev_fd)
{
	t_node	*head;
	t_node	*curr;

	head = nodes[0];
	curr = nodes[1];
	if (curr->fd_out != STDOUT_FILENO)
	{
		if (dup2(curr->fd_out, STDOUT_FILENO) == -1)
			exit_child("dup2 fd_out to file failed\n", head, lists, -1);
	}
	else if (curr->next)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit_child("dup2 fd_out failed\n", head, lists, fd[1]);
	}
	if (curr->fd_in != STDIN_FILENO)
	{
		if (dup2(curr->fd_in, STDIN_FILENO) == -1)
			exit_child("dup2 fd_in from file failed\n", head, lists, -1);
	}
	else
	{
		if (dup2((*prev_fd), STDIN_FILENO) == -1)
			exit_child("dup2 fd_in failed\n", head, lists, fd[0]);
	}
}

static void	exec_external(t_lists *lists, t_node *head, t_node *curr)
{
	char	*path_list;

	if (!curr->content->command)
		exit_child(NULL, head, lists, -1);
	path_list = get_path_list("PATH\0", curr->var_list->env);
	if (get_absolute_path(path_list, curr->content->command,
			curr))
		exit_child(NULL, head, lists, -1);
	execve(curr->content->command, curr->content->args, 0);
	exit_child("execv:\n", head, lists, -1);
}

void	execute_child(t_lists *lists, t_node **nodes, int *fd,
		int prev_fd)
{
	t_node	*head;
	t_node	*curr;

	head = nodes[0];
	curr = nodes[1];
	if (!curr->next)
		close(fd[1]);
	if (curr == head)
		close(fd[0]);
	redirect_fds(lists, nodes, fd, &prev_fd);
	if (is_built_in(curr->content->command))
	{
		find_built(&head, &lists);
		exit_child(NULL, head, lists, -1);
	}
	else
		exec_external(lists, head, curr);
}
