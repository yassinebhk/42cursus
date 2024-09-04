#include "minishell.h"

int	init_pipes(int **pipes, t_node *head)
{
	int	i;
	int	pos;
	int	fd[2];

	i = -1;
	pos = 0;
	*pipes = (int *)malloc(2 * sizeof(int) * (ft_len_node(head) - 1));
	if (!(*pipes))
		return (print_error("pipe array malloc ", ENO_MEM), 0);
	while (++i < ft_len_node(head) - 1)
	{
		if (pipe(fd) == -1)
			return (ft_putstr_fd("pipe function failed", 2), 0);
		pipes[0][pos++] = fd[0];
		pipes[0][pos++] = fd[1];
	}
	return (1);
}

void	close_pipes(int *pipes, int len)
{
	int	i;

	i = -1;
	while (++i < 2 * (len - 1))
		close(pipes[i]);
}

int	ft_open(char *file, int flag, int permission, int old_fd)
{
	if (old_fd > 2)
		close(old_fd);
	if (permission)
		return (open(file, flag, 0644));
	else
		return (open(file, flag));
}

int heredoc(void)
{
	return (1);
}

int	open_and_get_fd(t_node *tmp, int i, int *fd_in, int *fd_out)
{
	int		redir;
	char	*file;

	redir = tmp->content->redir[i].type;
	file = tmp->content->redir[i].filename;
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

	i = -1;
	tmp = *head;
	while (tmp)
	{
		fd_out = 1;
		fd_in = 0;
		while (++i < tmp->content->num_redir)
		{
			if (!open_and_get_fd(tmp, i, &fd_out, &fd_in))
				return (0);
		}
		tmp->fd_in = fd_in;
		tmp->fd_out = fd_out;
		tmp = tmp->next;
	}
	return (1);
}

void	ft_dup2(int *fd_in, int *fd_out)
{
	dup2(*fd_in, 0);
	dup2(*fd_out, 1);
	close(*fd_in);
	close(*fd_out);
}

void	execute_child(t_node *head, t_node *curr, int *pipes, int *pipe_pos)
{
	int		fd_in;
	int		fd_out;
	int		fd_tmp;
	char	*path_list;

	fd_in = curr->fd_in;
	fd_out = curr->fd_out;
	if (curr->next && curr->content->num_redir == 0)
	{
		fd_tmp = pipes[(*pipe_pos) + 1];
		pipes[(*pipe_pos) + 1] = pipes[(*pipe_pos) + 2];
		pipes[(*pipe_pos) + 2] = fd_tmp;		
	}
	if (!fd_in)
		fd_in = pipes[(*pipe_pos)];
	if (!(fd_out - 1))
		fd_out = pipes[(*pipe_pos) + 1];	
	ft_dup2(&fd_in, &fd_out);
	close_pipes(pipes, ft_len_node(head));
	(*pipe_pos) += 2;
	if (is_built_in(curr->content->command))
	{
		find_built(curr->content->args, curr->content->num_args,
			&(curr->var_list->env), &(curr->var_list->exp));
		free_list(head);
		free(pipes);
		_exit(0);
	}
	path_list = get_path_list("PATH\0", curr->var_list->env);
	if (!path_list)
	{
		ft_putstr_fd("variable not found", 2);
		free(head);
		free(pipes);
		return ;
	}
	if (!get_absolute_path(path_list, curr->content->command, curr))
	{
		ft_putstr_fd("command not found", 2);
		free(head);
		free(pipes);
		return ;
	}
	if (execv(curr->content->command, curr->content->args) == -1)
	{
		perror("execv: ");
		free(pipes);
		free_list(head);
	}
}

void	print_redir2(t_redir redir)
{
	printf("    Redirection type: %d\n", redir.type);
	printf("    Valid: %d\n", redir.valid);
	printf("    Filename: %s. (%ld)\n", redir.filename,
		ft_strlen(redir.filename));
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
	int	node_count;

	node_count = 0;
	while (node)
	{
		printf("       Command content     \n");
		print_command2(node->content);
		printf("  fd:\n");
		// Print additional fields (env, exp) if necessary
		// ...
		printf("    fd_in: %d\n",node->fd_in);
		printf("    fd_out: %d\n",node->fd_out);
		node = node->next;
		node_count++;
	}
	printf("\n-----------------------------------------------\n");
}

int	execute_commands(t_node **head)
{
	int		pid;
	int		pipe_pos;
	int		*pipes;
	t_node	*tmp;

	pipe_pos = 0;
	if (delete_backslash(head))
		return (1);
	if (!set_fd(head))
		return (1);
	print_list2(*head);
	if (!init_pipes(&pipes, *head))
		return (1);
	tmp = *head;
	while (tmp)
	{
		pid = fork();
		if (pid < 0)
			return (free(pipes), ft_putstr_fd("fork failed", 2), 1);
		else if (!pid)
			execute_child(*head, tmp, pipes, &pipe_pos);
		else
		{
			close_pipes(pipes, ft_len_node(*head));
			wait(NULL);
			//waitpid(-1, NULL, 0);
			wait(NULL);
			free(pipes);
		}
		tmp = tmp->next;
	}
	return (0);
}

// checker comandos para que no me entren caracteres especiales en el command
