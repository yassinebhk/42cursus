/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:09:37 by maxgarci          #+#    #+#             */
/*   Updated: 2025/04/09 10:45:53 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path_list(char *command, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(command, env->key))
			return (env->var);
		env = env->next;
	}
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("path variable not found at env.\n", 2);
	return (NULL);
}

int	is_built_in(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "exit"))
		return (1);
	return (0);
}

int	get_absolute_path(char *path_list, char *command, t_node *head)
{
	int		pos;
	char	*tmp;
	char	**split;
	char	*path;
	char	*absolute_dir;

	if (!access((head)->content->command, X_OK))
		return (FN_SUCCESS);
	pos = -1;
	split = ft_split(path_list, ':');
	while (split[++pos])
	{
		path = split[pos];
		tmp = ft_strjoin(path, "/");
		absolute_dir = ft_strjoin(tmp, command);
		if (!access(absolute_dir, e_X_OK))
		{
			free(head->content->command);
			head->content->command = ft_strdup(absolute_dir);
			return (ft_free(split), free(tmp), free(absolute_dir), FN_SUCCESS);
		}
		free(tmp);
		free(absolute_dir);
	}
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
	return (ft_free(split), FN_FAILURE);
}

static int	exec_comm(t_node *head, int input, int output)
{
	pid_t	pid;
	int		inpos;
	int		outpos;
	int		status;

	inpos = head->fd_in;
	outpos = head->fd_out;
	status = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (1);
	}
	else if (!pid)
	{
		if (input == r_input)
		{
			head->fd_in = open(head->content->redir[inpos]->filename, O_RDONLY);
			if (head->fd_in < 0)
			{
				perror("open error");
				exit(EXIT_FAILURE);
			}
			if (dup2(head->fd_in, STDIN_FILENO) < 0)
			{
				perror("dup2 error");
				exit(EXIT_FAILURE);
			}
			close(head->fd_in);
		}
		if (input == r_heredoc)
		{
			read_heredoc(head->content->redir[inpos]->filename);
			head->fd_in = open(HEREDOC_FILENAME, O_RDONLY); // cambiar por un archivo temporal 
			if (head->fd_in < 0)
			{
				perror("open error");
				exit(EXIT_FAILURE);
			}
			if (dup2(head->fd_in, STDIN_FILENO) < 0)
			{
				perror("dup2 error");
				exit(EXIT_FAILURE);
			}
			close(head->fd_in);
		}
		if (output == r_output)
		{
			head->fd_out = open(head->content->redir[outpos]->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (head->fd_out < 0)
			{
				perror("open error");
				exit(EXIT_FAILURE);
			}
			if (dup2(head->fd_out, STDOUT_FILENO) < 0)
			{
				perror("dup2 error");
				exit(EXIT_FAILURE);
			}
			close(head->fd_out);
		}
		if (output == r_append)
		{
			head->fd_out = open(head->content->redir[outpos]->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (head->fd_out < 0)
			{
				perror("open error");
				exit(EXIT_FAILURE);
			}
			if (dup2(head->fd_out, STDOUT_FILENO) < 0)
			{
				perror("dup2 error");
				exit(EXIT_FAILURE);
			}
			close(head->fd_out);
		}
		if (!access((head)->content->command, X_OK))
			execve(head->content->command, head->content->args, NULL);
		else
			perror(NO_EXEC_PERM_ERROR);
		perror("execve failed");
		free_node(head);
		exit (EXIT_FAILURE);
	}
	else
		wait(&status);
	if (input == r_heredoc)
		unlink(HEREDOC_FILENAME);
	return (status);
}

static int	find_output_redirection(t_command *comm)
{
	int	outpos;

	outpos = -1;
	while (++outpos < comm->num_redir)
	{
		if (comm->redir[outpos]->type == r_output
			|| comm->redir[outpos]->type == r_append)
			return (1);
	}
	return (0);
}

static int	handle_output_redirections(t_node *head, int input)
{
	int			outpos;
	t_command	*c;

	outpos = -1;
	c = head->content;
	while (++outpos < c->num_redir)
	{
		if (c->redir[outpos]->type == r_output
			|| c->redir[outpos]->type == r_append)
		{
			head->fd_out = outpos;
			if (exec_comm(head, input, c->redir[outpos]->type))
				return (1);
		}
	}
	return (0);
}

static int	find_input_redirection(t_command *comm)
{
	int	inpos;

	inpos = -1;
	while (++inpos < comm->num_redir)
	{
		if (comm->redir[inpos]->type == r_input
			|| comm->redir[inpos]->type == r_heredoc)
			return (1);
	}
	return (0);
}

static int	handle_input_redirections(t_node *head, int output_exists)
{
	int			inpos;
	t_command	*c;

	inpos = -1;
	c = head->content;
	while (++inpos < c->num_redir)
	{
		if (c->redir[inpos]->type == r_input
			|| c->redir[inpos]->type == r_heredoc)
		{
			head->fd_in = inpos;
			if (output_exists)
			{
				if (handle_output_redirections(head, c->redir[inpos]->type))
					return (1);
			}
			else if (exec_comm(head, c->redir[inpos]->type, 0))
				return (1);
		}
	}
	return (0);
}

static int	redirect(t_node *head)
{
	int	num_input;
	int	num_output;

	num_input = find_input_redirection(head->content);
	num_output = find_output_redirection(head->content);
	if (num_input > 0)
	{
		if (handle_input_redirections(head, num_output))
			return (1);
	}
	else if (num_output > 0)
	{
		if (handle_output_redirections(head, 0))
			return (1);
	}
	else
	{
		if (exec_comm(head, 0, 0))
			return (1);
	}
	return (0);
}

int	execute_one_command(t_node **head, t_lists *lists)
{
	char	*path_list;

	if (is_built_in((*head)->content->command))
		return (execute_built(head, lists));
	path_list = get_path_list("PATH\0", lists->env);
	if (!path_list)
		return (VARIABLE_NOT_FOUND);
	if (get_absolute_path(path_list, (*head)->content->command, *head))
		return (COMMAND_NOT_FOUND);
	if (redirect(*head))
		return (1);
	return (0);
}
