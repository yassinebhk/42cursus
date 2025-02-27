/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:05:56 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/02/27 11:53:45 by maxgarci         ###   ########.fr       */
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

int	heredoc(void)
{
	return (1);
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
		*fd_in = heredoc();
	// hay que hacer el heredoc antes de pasar al siguiente (foto)
	if (*fd_in == -1 || *fd_out == -1)
	{
		ft_putstr_fd("Error opening ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (0);
	}
	return (1);
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
			if (!open_and_get_fd(tmp, i, &fd_in, &fd_out))
				return (0);
		}
		tmp->fd_in = fd_in;
		tmp->fd_out = fd_out;
		tmp = tmp->next;
	}
	return (1);
}

void	print_redir2(t_redir *redir)
{
	printf("    Redirection->type: %d\n", redir->type);
	printf("    Filename: %s. (%ld)\n", redir->filename,
		ft_strlen(redir->filename));
}

void	print_command2(t_command *cmd)
{
	if (!cmd)
	{
		printf("    (null)\n");
		return ;
	}
	printf("  Command: %s\n", cmd->command);
	printf("  Number of arguments: %d\n", cmd->num_args);
	if (cmd->num_args > 0 && cmd->args)
	{
		printf("  Arguments:\n");
		for (int i = 0; i < cmd->num_args; i++)
			printf("    arg[%d]: %s. (%ld)\n", i, cmd->args[i],
				ft_strlen(cmd->args[i]));
	}
	else
	{
		printf("  No arguments.\n");
	}
	printf("  Number of redirs: %d\n", cmd->num_redir);
	if (cmd->num_redir && cmd->redir)
	{
		printf("  Redirections:\n");
		for (int i = 0; i < cmd->num_redir; i++)
			print_redir2(cmd->redir[i]);
	}
	else
		printf("  No redirections.\n");
}

void	print_list2(t_node *node)
{
	while (node)
	{
		printf("       Command content     \n");
		print_command2(node->content);
		printf("  fd:\n");
		// Print additional fields (env, exp) if necessary
		// ...
		printf("    fd_in: %d\n", node->fd_in);
		printf("    fd_out: %d\n", node->fd_out);
		node = node->next;
	}
	printf("\n-----------------------------------------------\n");
}

void	ft_dup2(int *fd_in, int *fd_out)
{
	dup2(*fd_in, STDIN_FILENO);
	dup2(*fd_out, STDOUT_FILENO);
	close(*fd_in);
	close(*fd_out);
}

void	execute_child(t_lists *lists, t_node *head, t_node *curr, int *fd,
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
		free_args(lists->env, lists->exp);
	}
	if (curr->fd_out != STDOUT_FILENO)
	{
		if (dup2(curr->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_out to file failed ");
			free_list(head);
			free_args(lists->env, lists->exp);
		}
	}
	else if (curr->next)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_out failed ");
			free_list(head);
			free_args(lists->env, lists->exp);
		}
		close(fd[1]);
	}
	if (curr->fd_in != STDIN_FILENO)
	{
		if (dup2(curr->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in from file failed ");
			free_list(head);
			free_args(lists->env, lists->exp);
		}
	}
	else
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in failed ");
			free_list(head);
			free_args(lists->env, lists->exp);
		}
		close(fd[0]);
	}
	if (is_built_in(curr->content->command))
	{
		find_built(&head, &lists);
		free_list(head);
		free_args(lists->env, lists->exp);
		exit(0);
	}
	else
	{
		path_list = get_path_list("PATH\0", curr->var_list->env);
		if (!path_list || !get_absolute_path(path_list, curr->content->command,
				curr))
		{
			free_list(head);
			free_args(lists->env, lists->exp);
			exit(COMMAND_NOT_FOUND);
		}
		execve(curr->content->command, curr->content->args, 0);
		perror("execv: ");
		free_list(head);
		free_args(lists->env, lists->exp);
		exit(EXIT_FAILURE);
	}
}

int	execute_commands(t_node **head, t_lists *lists)
{
	int		pid;
	int		fd[2];
	int		prev_fd_in;
	t_node	*tmp;

	if (!set_fd(head))
		return (EXIT_FAILURE);
	tmp = *head;
	prev_fd_in = tmp->fd_in;
	while (tmp)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe function failed");
			return (EXIT_FAILURE);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
			return (EXIT_FAILURE);
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
			wait(0);
		}
		close(prev_fd_in);
		prev_fd_in = dup(fd[0]);
		close(fd[0]);
		tmp = tmp->next;
	}
	if (prev_fd_in != -1)
		close(prev_fd_in);
	return (0);
}

// checker comandos para que no me entren caracteres especiales en el command
