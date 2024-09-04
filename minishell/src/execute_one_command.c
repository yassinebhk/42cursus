#include "minishell.h"

char	*get_path_list(char *command, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(command, env->key))
			return (env->var);
		env = env->next;
	}
	ft_putstr_fd("path variable not found at env.", 2);
	return (NULL);
}

int	is_built_in(char *command)
{
	if (!ft_strcmp(command, "echo\0") || !ft_strcmp(command, "cd\0")
		|| !ft_strcmp(command, "pwd\0") || !ft_strcmp(command, "export\0")
		|| !ft_strcmp(command, "unset\0") || !ft_strcmp(command, "env\0")
		|| !ft_strcmp(command, "exit\0"))
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

	pos = -1;
	split = ft_split(path_list, ':');
	while (split[++pos])
	{
		path = split[pos];
		tmp = ft_strjoin(path, "/");
		absolute_dir = ft_strjoin(tmp, command);
		if (!access(absolute_dir, e_X_OK))
		{
			head->content->command = ft_strdup(absolute_dir);
			return (ft_free(split), free(tmp), free(absolute_dir), 1);
		}
	}
	ft_putstr_fd("absolute path not found.\n", 2);
	return (ft_free(split), free(tmp), free(absolute_dir), 0);
}

static int	reset_std(int stdin_copy, int stdout_copy)
{
	if (dup2(stdin_copy, STDIN_FILENO) < 0 || dup2(stdout_copy, STDOUT_FILENO) < 0)
	{
		perror("error reseting std");
		return (1);
	}
	return (0);
}

static int	save_std_streams(int *stdin_copy, int *stdout_copy)
{
	*stdin_copy = dup(STDIN_FILENO);
	*stdout_copy = dup(STDOUT_FILENO);
	if (*stdin_copy < 0 || *stdout_copy < 0)
	{
		perror("dup copy error");
		return (1);
	}
	return (0);
}

static int	exec_comm(t_node *head)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return (1);
	}
	else if (pid)
		wait(&status);
	else
	{
		if (execv((head)->content->command, (head)->content->args) == -1)
		{
			printf("Error al ejecutar execv: %s\n", strerror(errno));
			_exit(1);
		}
		_exit(0);
	}
	return (status);
}

static int	find_output_redirection(t_command *comm)
{
	int	outpos;

	outpos = -1;
	while (++outpos < comm->num_redir)
	{
		if (comm->redir[outpos].type == r_output ||\
				comm->redir[outpos].type == r_append)
			return (1);
	}
	return (0);
}

static int	handle_output_redirections(t_node *head)
{
	int	outpos;
	t_command	*c;

	outpos = -1;
	c = head->content;
	while (++outpos < c->num_redir)
	{
		if (c->redir[outpos].type == r_output)
			head->fd_out = open(c->redir[outpos].filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (c->redir[outpos].type == r_append)
			head->fd_out = open(c->redir[outpos].filename, O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (head->fd_out < 0)
		{
			perror("output error opening the file");
			return (1);
		}
		else if (head->fd_out != STDOUT_FILENO)
		{
			if (dup2(head->fd_out, STDOUT_FILENO))
			{
				perror("output error dup2");
				return (1);
			}
			close(head->fd_out);
		}
		if (exec_comm(head))
			return (1);
	}
	return (0);
}

static int	find_input_redirection(t_command *comm)
{
	int	inpos;

	inpos = -1;
	while (++inpos < comm->num_redir)
	{
		if (comm->redir[inpos].type == r_input)
			return (1);
	}
	return (0);
}

static int	handle_input_redirections(t_node *head)
{
	int	inpos;
	t_command	*c;

	inpos = -1;
	c = head->content;
	while (++inpos < c->num_redir)
	{
		if (c->redir[inpos].type == r_input)
		{
			head->fd_in = open(c->redir[inpos].filename, O_RDONLY);
			if (head->fd_in < 0)
			{
				perror("input error opening the file");
				return (1);
			}
			if (dup2(head->fd_in, STDIN_FILENO) < 0)
			{
				perror("intput error dup2");
				return (1);
			}
			close(head->fd_in);
			if (find_output_redirection(head->content))
			{
				if (handle_output_redirections(head))
					return (1);
			}
			else if(exec_comm(head))
				return (1);
		}
	}
	return (0);
}

static int	redirect(t_node *head)
{
	int			stdin_copy;
	int			stdout_copy;

	if (save_std_streams(&stdin_copy, &stdout_copy))
		return (1);
	if (find_input_redirection(head->content))
	{
		if (handle_input_redirections(head))
			return (1);
	}
	else if (find_output_redirection(head->content))
	{
		if (handle_output_redirections(head))
			return (1);
	}
	else if (exec_comm(head))
		return (1);
	if (reset_std(stdin_copy, stdout_copy))
		return (1);
	return (0);
}

int	execute_one_command(t_node *head)
{
	char	*path_list;

	if (is_built_in((head)->content->command))
		return (find_built((head)->content->args, (head)->content->num_args,
				&(head)->var_list.env, &(head)->var_list.exp));
	path_list = get_path_list("PATH\0", (head)->var_list.env);
	if (!path_list)
		return (VARIABLE_NOT_FOUND);
	if (!get_absolute_path(path_list, (head)->content->command, (head)))
		return (COMMAND_NOT_FOUND);
	if(redirect(head))
		return (1);
	return (0);
}
