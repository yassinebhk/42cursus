/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:05:56 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/03/22 11:00:11 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_open(char *file, int flag, int permission, int old_fd)
{
	if (old_fd > 2)
		close(old_fd);
	if (permission)
		return (open(file, flag, 0644));
	else
		return (open(file, flag));
}

int	heredoc(char *file)
{
	int	fd_in;

	read_heredoc(file);
	fd_in = open(HEREDOC_FILENAME, O_RDONLY);
	return (fd_in);
}

int	open_and_get_fd(t_node *tmp, int i, int *fd_in, int *fd_out)
{
	int		redir;
	char	*file;

	redir = tmp->content->redir[i]->type;
	file = tmp->content->redir[i]->filename;
	if (redir == 1)
		*fd_out = ft_open(file, O_CREAT | O_WRONLY | O_TRUNC, 1, tmp->fd_out);
	else if (redir == 2)
		*fd_out = ft_open(file, O_CREAT | O_APPEND | O_WRONLY, 1, tmp->fd_out);
	else if (redir == 3)
		*fd_in = ft_open(file, O_RDONLY, 0, tmp->fd_in);
	else if (redir == 4)
		*fd_in = heredoc(file);
	if (*fd_in < 0 || *fd_out < 0)
	{
		ft_putstr_fd("Error opening ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (FN_FAILURE);
	}
	return (FN_SUCCESS);
}

int	set_fd(t_node **head)
{
	int		i;
	int		fd_out;
	int		fd_in;
	t_node	*tmp;

	tmp = *head;
	while (tmp)
	{
		i = -1;
		fd_out = 1;
		fd_in = 0;
		while (++i < tmp->content->num_redir)
		{
			if (open_and_get_fd(tmp, i, &fd_in, &fd_out))
				return (FN_FAILURE);
		}
		tmp->fd_in = fd_in;
		tmp->fd_out = fd_out;
		tmp = tmp->next;
	}
	return (FN_SUCCESS);
}

int	execute_child(t_lists *lists, t_node *head, t_node *curr, int *fd,
		int prev_fd)
{
	char	*path_list;

	if (!curr->next)
		close(fd[1]);
	if (curr == head)
		close(fd[0]);
	if (!curr->content->command)
	{
		free_list(head);
		free_lists(lists->env, lists->exp);
	}
	if (curr->fd_out != STDOUT_FILENO)
	{
		if (dup2(curr->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_out to file failed ");
			free_list(head);
			free_lists(lists->env, lists->exp);
		}
	}
	else if (curr->next)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_out failed ");
			free_list(head);
			free_lists(lists->env, lists->exp);
		}
		close(fd[1]);
	}
	if (curr->fd_in != STDIN_FILENO)
	{
		if (dup2(curr->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in from file failed ");
			free_list(head);
			free_lists(lists->env, lists->exp);
		}
	}
	else
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in failed ");
			free_list(head);
			free_lists(lists->env, lists->exp);
		}
		close(fd[0]);
	}
	if (is_built_in(curr->content->command))
	{
		find_built(&head, &lists);
		free_list(head);
		free_lists(lists->env, lists->exp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		path_list = get_path_list("PATH\0", curr->var_list->env);
		if (!path_list || get_absolute_path(path_list, curr->content->command,
				curr))
		{
			free_list(head);
			free_lists(lists->env, lists->exp);
			exit(EXIT_FAILURE);
		}
		execve(curr->content->command, curr->content->args, 0);
		perror("execv: ");
		free_list(head);
		free_lists(lists->env, lists->exp);
		exit(EXIT_FAILURE);
	}
}

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
			execute_child(lists, *head, tmp, fd, prev_fd_in);
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
