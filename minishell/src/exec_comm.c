/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:07:54 by maxgarci          #+#    #+#             */
/*   Updated: 2025/04/20 17:18:33 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_and_dup(int *fd, const char *filename, int flag_fileno[2],
						mode_t mode)
{
	int	oflag;
	int	fileno;

	oflag = flag_fileno[0];
	fileno = flag_fileno[1];
	if (!mode)
		*fd = open(filename, oflag);
	else
		*fd = open(filename, oflag, mode);
	if (*fd < 0)
	{
		perror("open error");
		exit(EXIT_FAILURE);
	}
	if (dup2(*fd, fileno) < 0)
	{
		perror("dup2 error");
		exit(EXIT_FAILURE);
	}
	close(*fd);
}

static void	redirect_uniq_child(t_node *head, int input, int output)
{
	int	inpos;
	int	outpos;

	inpos = head->fd_in;
	outpos = head->fd_out;
	if (input == r_input)
		open_and_dup(&(head->fd_in), head->content->redir[inpos]->filename,
			(int [2]){O_RDONLY, STDIN_FILENO}, 0);
	if (input == r_heredoc)
	{
		read_heredoc(head->content->redir[inpos]->filename);
		open_and_dup(&(head->fd_in), HEREDOC_FILENAME,
			(int [2]){O_RDONLY, STDIN_FILENO}, 0);
	}
	if (output == r_output)
		open_and_dup(&(head->fd_out), head->content->redir[outpos]->filename,
			(int [2]){O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO}, 0644);
	if (output == r_append)
		open_and_dup(&(head->fd_out), head->content->redir[outpos]->filename,
			(int [2]){O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO}, 0644);
}

static int	child_comm_execution(t_node *head)
{
	if (!access((head)->content->command, X_OK))
		execve(head->content->command, head->content->args, NULL);
	else
		perror(NO_EXEC_PERM_ERROR);
	perror("execve failed");
	free_node(head);
	exit(EXIT_FAILURE);
}

int	exec_comm(t_node *head, int input, int output)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (FN_FAILURE);
	}
	else if (!pid)
	{
		redirect_uniq_child(head, input, output);
		child_comm_execution(head);
	}
	else
		wait(&status);
	if (input == r_heredoc)
		unlink(HEREDOC_FILENAME);
	return (status);
}
